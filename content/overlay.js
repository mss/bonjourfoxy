var bonjourfoxy = {
  startup: function() {
    this.strings = document.getElementById("bonjourfoxy-strings");
    this.IDSDMANAGER = Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
    this.prefs = Components.classes["@mozilla.org/preferences-service;1"]
            .getService(Components.interfaces.nsIPrefService)
            .getBranch("extensions.bonjourfoxy.");
    this.prefs.QueryInterface(Components.interfaces.nsIPrefBranch2);
    this.prefs.addObserver("", this, false);
    this.observerService = Components.classes["@mozilla.org/observer-service;1"]
                          .getService(Components.interfaces.nsIObserverService);
    this.setRegtypeObservers();
    this.displayStatusBarIcon();
    this.setStatusBarIcon();
  },
  shutdown: function() {
    this.removeRegtypeObservers();
    this.prefs.removeObserver("", this);
  },
  observe: function(subject, topic, data)
    {
    if (topic == "nsPref:changed")  {
        switch(data)
        {
            case "statusbaricon":
                this.displayStatusBarIcon();
            break;
            case "hst":
                this.setRegtypeObservers();
            break;
        }
    }
    if (topic.match(/^dsd_service_/)) {
        this.setStatusBarIcon();
    }
  },
  regtypes: [],
  updateRegtypes: function()    {
    var storageService = Components.classes["@mozilla.org/storage/service;1"]
                    .getService(Components.interfaces.mozIStorageService);        
    var dbFile = Components.classes["@mozilla.org/file/directory_service;1"]
                    .getService(Components.interfaces.nsIProperties)
                    .get("ProfD", Components.interfaces.nsIFile);
    dbFile.append("bonjourfoxy.sqlite");
    var DBConn = storageService.openDatabase(dbFile);
    var sqlServices = DBConn.createStatement("                   \
SELECT                                                                  \
    Services.label as label,                                            \
    Services.regtype as regtype,                                        \
    GROUP_CONCAT(                                                       \
        DISTINCT ServiceSubtypes.label||':'||ServiceSubtypes.subtype    \
    ) as subtypes                                                       \
FROM Services                                                           \
LEFT OUTER JOIN ServiceSubtypes ON Services.id = ServiceSubtypes.s_id   \
GROUP BY Services.regtype, Services.scheme, Services.label;             ");
    var newRegtypes={};
    while(sqlServices.executeStep()) {
        var label = sqlServices.getUTF8String(0);
        var regtype = sqlServices.getUTF8String(1);
        try { var subtypePairs = sqlServices.getUTF8String(2).split(","); }
        catch (e) { var subtypePairs = []; }
        // dump ([label,regtype,subtypePairs,"\n"].join(' '));
        // newVisibleData.push([label, true, false, -1]);
        if(!newRegtypes[regtype])   {
            newRegtypes[regtype] = {
                label: label,
                subtypes: {},
            };
        }
        for (var i=0;i<subtypePairs.length;i++)  {
            // dump(subtypePairs[i]+"\n");
            var subtypePairsA = subtypePairs[i].split(':');
            var subtypeLabel = subtypePairsA[0];
            var subtypeType = subtypePairsA[1];
            // dump (["subtypeLabel",subtypeLabel,"subtypeType",subtypeType].join('\t')+"\n");
            // newVisibleData.push([subtypeLabel, true, false, -1]);
            if(!newRegtypes[regtype]["subtypes"][subtypeType])  {
                newRegtypes[regtype]["subtypes"][subtypeType] = subtypeLabel;
                // dump("newRegtypes[regtype]['subtypes'][subtypeType]" + newRegtypes[regtype]["subtypes"][subtypeType] + "\n");
            }
        }
    }
    this.regtypes = newRegtypes;
  },
  removeRegtypeObservers: function()    {
    for (regtype in this.regtypes)    {
        this.observerService.removeObserver(this, "dsd_service_rmv:"+regtype, false);
        this.observerService.removeObserver(this, "dsd_service_add:"+regtype, false);
    }
  },
  addRegtypeObservers: function() {
    for (regtype in this.regtypes)    {
        this.observerService.addObserver(this, "dsd_service_rmv:"+regtype, false);
        this.observerService.addObserver(this, "dsd_service_add:"+regtype, false);
    }
  },
  setRegtypeObservers: function()    {
    this.removeRegtypeObservers();
    this.updateRegtypes();
    this.addRegtypeObservers();
  },
  displayStatusBarIcon: function()  {
    if (this.prefs.getBoolPref("statusbaricon")) {
        document.getElementById('bonjourStatusIcon').setAttribute("style","display:block;");
    } else {
        document.getElementById('bonjourStatusIcon').setAttribute("style","display:none;");
    }
  },
  setStatusBarIcon: function()   {
    document.getElementById('bonjourStatusIcon').setAttribute("image","chrome://bonjourfoxy/content/status_bw.png");
    for (regtype in this.regtypes)    {
        dump(regtype + this.IDSDMANAGER.getDiscoveredServicesCount(regtype,null) + "\n");
        if (this.IDSDMANAGER.getDiscoveredServicesCount(regtype,null)>0)  {
            document.getElementById('bonjourStatusIcon').setAttribute("image","chrome://bonjourfoxy/content/status_color.png");
            return;
            }
    }
  },
  onMenuItemCommand: function(e) {
    toggleSidebar("viewBonjourServices");
  },
  onToolbarButtonCommand: function(e) {
    // just reuse the function above
    bonjourfoxy.onMenuItemCommand(e);
  },
  openPreferences: function(e)  {
    var paneID = "bonjourfoxy-prefpane";
    var features = "chrome,titlebar,toolbar,centerscreen,true,dialog=no"
    var wm = Components.classes["@mozilla.org/appshell/window-mediator;1"]
                    .getService(Components.interfaces.nsIWindowMediator);
    var win = wm.getMostRecentWindow("Browser:Preferences");
    if (win) {
        win.focus();
        if (paneID) {
            var pane = win.document.getElementById(paneID);
            win.document.documentElement.showPane(pane);
        }
    } else {
        openDialog("chrome://bonjourfoxy/content/options.xul",
              "Preferences", features, paneID);
    }
  },
  menuAddServices: function()   {
    var menu = document.getElementById("bonjourMenuPopup");
    while (menu.childNodes.length>4)   {
        menu.removeChild(menu.childNodes[menu.childNodes.length-1]);
    }
    var servicesFound=false;
    var newMenuPopups = {};
    for (regtype in this.regtypes)  {
        var discoveredServices = this.IDSDMANAGER.getDiscoveredServices(regtype, null);
        if (discoveredServices.length>0)    {
            servicesFound=true;
            for (var i=0;i<discoveredServices.length;i++)   {
                var discoveredService = discoveredServices.queryElementAt(i,Components.interfaces.nsIArray);
                var item = document.createElement('menuitem');
                item.setAttribute('label', discoveredService.queryElementAt(2,Components.interfaces.nsIVariant));
                item.setAttribute('oncommand', [
                    'openLink("default",',
                    discoveredService.queryElementAt(3,Components.interfaces.nsIVariant),
                    ')'].join(''));
                try { var subtypes = discoveredService.queryElementAt(4,Components.interfaces.nsIVariant); }
                catch (e) { var subtypes = null; }
                if (subtypes)   {
                    if (subtypes.indexOf(',')==-1) {
                        if(!newMenuPopups[this.regtypes[regtype]["subtypes"][subtypes]]) {
                            newMenuPopups[this.regtypes[regtype]["subtypes"][subtypes]]=document.createElement('menupopup');
                        }
                        newMenuPopups[this.regtypes[regtype]["subtypes"][subtypes]].appendChild(item);
                    } else {
                        var subtypesA = subtypes.split(',');
                        for(j=0;j<subtypesA.length;j++) {
                            if(!newMenuPopups[this.regtypes[regtype]["subtypes"][subtypesA[j]]]) {
                                newMenuPopups[this.regtypes[regtype]["subtypes"][subtypesA[j]]]=document.createElement('menupopup');
                            }
                            newMenuPopups[this.regtypes[regtype]["subtypes"][subtypesA[j]]].appendChild(item);                            
                        }
                    }
                } else {
                    if(!newMenuPopups[this.regtypes[regtype].label]) {
                        newMenuPopups[this.regtypes[regtype].label]=document.createElement('menupopup');
                    }
                    newMenuPopups[this.regtypes[regtype].label].appendChild(item);
                }
            }
        }
    }
    if (!servicesFound) {
        var item = document.createElement("menuitem");
        item.setAttribute("label","No services found");
        item.setAttribute("disabled",true);
        menu.appendChild(item);
    } else {
        for (menupopup in newMenuPopups)   {
            var newMenu = document.createElement('menu');
            newMenu.setAttribute('label',menupopup);
            newMenu.appendChild(newMenuPopups[menupopup]);
            menu.appendChild(newMenu);
        }
    }
  }
};

window.addEventListener("load", function(e) { bonjourfoxy.startup(); }, false);
window.addEventListener("unload", function(e) { bonjourfoxy.shutdown(); }, false);
