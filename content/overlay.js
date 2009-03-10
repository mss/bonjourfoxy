var bonjourfoxy = {
  onLoad: function() {
    // initialization code
    this.initialized = true;
    this.strings = document.getElementById("bonjourfoxy-strings");
    var obj=Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
    obj.discoverServices("_http._tcp.",null);
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

function menuEventHandler(element) {
    window.alert(element.getAttribute('value'));
};

function menuAddServices() {
    var menu = document.getElementById("bonjourMenuPopup");
    while (menu.childNodes.length>3)   {
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
            var foo = discoveredService.queryElementAt(2,Components.interfaces.nsIVariant);
            var item = document.createElement('menuitem');
            item.setAttribute('label', foo);
            item.setAttribute('oncommand','openLink("default","' + [
                escape(discoveredService.queryElementAt(2,Components.interfaces.nsIVariant)),
                escape(discoveredService.queryElementAt(1,Components.interfaces.nsIVariant)),
                escape(discoveredService.queryElementAt(0,Components.interfaces.nsIVariant))
                ].join('","')+'");');
            menu.appendChild(item);
        }
    }
}

window.addEventListener("load", function(e) { bonjourfoxy.onLoad(e); }, false);

function dsdOverlayObserver()
{
  this.register();
}
dsdOverlayObserver.prototype = {
  observe: function(subject, topic, data) {
     var obj=Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
     if (obj.getDiscoveredServicesCount("_http._tcp.",null)>0)
     {
        document.getElementById('bonjourStatusIcon').style.display = "";
        document.getElementById('bonjourStatusIcon').setAttribute("image","chrome://bonjourfoxy/content/status_color.png");
     } else {
        document.getElementById('bonjourStatusIcon').style.display = "none";
        document.getElementById('bonjourStatusIcon').setAttribute("image","chrome://bonjourfoxy/content/transparent.gif");
     }
     if (topic=="dsd_service_add__http._tcp.")
     {
         var prefs = Components.classes["@mozilla.org/preferences-service;1"]
                        .getService(Components.interfaces.nsIPrefService);
         prefs = prefs.getBranch("extensions.bonjourfoxy.");
         if (prefs.getBoolPref("alerts"))
         {
             // kludgey....
             if (obj.getServiceNameCount(data)==1)  {
                 var alertsService = Components.classes["@mozilla.org/alerts-service;1"].getService(Components.interfaces.nsIAlertsService);
                 alertsService.showAlertNotification(null,"Service Discovered",data,null,null,null);
             }
         }
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