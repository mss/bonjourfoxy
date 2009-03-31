var bonjourfoxy = {
  startup: function() {
    // initialization code
    this.initialized = true;
    this.strings = document.getElementById("bonjourfoxy-strings");
    this.IDSDMANAGER = Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
    // this.IDSDMANAGER.discoverServices("_http._tcp.",null);
    this.prefs = Components.classes["@mozilla.org/preferences-service;1"]
            .getService(Components.interfaces.nsIPrefService)
            .getBranch("extensions.bonjourfoxy.");
    this.prefs.QueryInterface(Components.interfaces.nsIPrefBranch2);
    this.prefs.addObserver("", this, false);
    this.displayStatusBarIcon();
  },
  shutdown: function() {
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
        }
    }
  },
  displayStatusBarIcon: function()  {
    if (this.prefs.getBoolPref("statusbaricon")) {
        document.getElementById('bonjourStatusIcon').setAttribute("style","display:block;");
    } else {
        document.getElementById('bonjourStatusIcon').setAttribute("style","display:none;");
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
  }
};

/*
function menuEventHandler(element) {
    window.alert(element.getAttribute('value'));
};
*/

function menuAddServices() {
    var menu = document.getElementById("bonjourMenuPopup");
    while (menu.childNodes.length>4)   {
        menu.removeChild(menu.childNodes[menu.childNodes.length-1]);
    }

    var obj=Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
    obj.discoverServices("_http._tcp.",null);

    var discoveredServices = obj.getDiscoveredServices("_http._tcp.",null);

    if (discoveredServices.length==0)   {
        var item = document.createElement("menuitem");
        item.setAttribute("label","No services found");
        item.setAttribute("disabled",true);
        menu.appendChild(item);
    } else {            
        for(var i=0;i<discoveredServices.length;i++)   {
            var discoveredService = discoveredServices.queryElementAt(i,Components.interfaces.nsIArray);
            var item = document.createElement('menuitem');
            item.setAttribute('label', discoveredService.queryElementAt(2,Components.interfaces.nsIVariant));
            item.setAttribute('oncommand', [
                'openLink("default",',
                discoveredService.queryElementAt(3,Components.interfaces.nsIVariant),
                ')'].join(''));
            menu.appendChild(item);
        }
    }
}

window.addEventListener("load", function(e) { bonjourfoxy.startup(); }, false);
window.addEventListener("unload", function(e) { bonjourfoxy.shutdown(); }, false);


function dsdOverlayObserver()
{
  this.register();
}
dsdOverlayObserver.prototype = {
  observe: function(subject, topic, data) {
     var obj=Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
     if (obj.getDiscoveredServicesCount("_http._tcp.",null)>0)
     {
        document.getElementById('bonjourStatusIcon').setAttribute("image","chrome://bonjourfoxy/content/status_color.png");
     } else {
        document.getElementById('bonjourStatusIcon').setAttribute("image","chrome://bonjourfoxy/content/transparent.gif");
     }
  },
  register: function() {
    var observerService = Components.classes["@mozilla.org/observer-service;1"]
                          .getService(Components.interfaces.nsIObserverService);
    observerService.addObserver(this, "dsd_service_add__http._tcp.", false);
    observerService.addObserver(this, "dsd_service_rmv__http._tcp.", false);
  },
  unregister: function() {
    var observerService = Components.classes["@mozilla.org/observer-service;1"]
                            .getService(Components.interfaces.nsIObserverService);
    observerService.removeObserver(this, "dsd_service_add__http._tcp.", false);
    observerService.removeObserver(this, "dsd_service_rmv__http._tcp.", false);
  }
}

var dsdOverlayObserverInstance = new dsdOverlayObserver();
