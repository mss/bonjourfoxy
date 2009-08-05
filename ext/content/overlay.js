var bonjourfoxy = {
  startup: function() {
    this.strings = document.getElementById("string-bundle");
    this.prefs = Components.classes["@mozilla.org/preferences-service;1"]
            .getService(Components.interfaces.nsIPrefService)
            .getBranch("extensions.bonjourfoxy.");
    this.prefs.QueryInterface(Components.interfaces.nsIPrefBranch2);
    this.prefs.addObserver("", this, false);
    this.observerService = Components.classes["@mozilla.org/observer-service;1"]
                          .getService(Components.interfaces.nsIObserverService);
    this.displayStatusBarIcon();
    this.setStatusBarIcon();
    if (/Win/.test(navigator.platform)) {
        document.getElementById('bonjourfoxyMenuPref').setAttribute('label', this.strings.getString('winPrefLabel'));
    } else {
        document.getElementById('bonjourfoxyMenuPref').setAttribute('label', this.strings.getString('unixPrefLabel'));
    }
    this.bfbrowse = Components.classes["@bonjourfoxy.net/bfbrowse;1"].createInstance(Components.interfaces.BFBrowse);
    this.bfbrowse.callback = this.browseCallback();
    this.bfbrowse.interfaceIndex = 0;
    this.bfbrowse.registrationType = "_http._tcp";
    this.bfbrowse.registrationDomain = "";
    this.bfbrowse.browse();
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
            case "hst":
                this.setRegtypeObservers();
            break;
        }
    }
  },
  services: Object(),
  serviceCount: 0,
  browseCallback: function() {
      var localcontext = this;
      return function(aError, aAdd, aInterfaceIndex, aServiceName, aRegistrationType, aRegistrationDomain)  {
        var context = localcontext;
        if (!aError) {
            if (aAdd)   {
                if (!context.services[aServiceName])    {
                    context.serviceCount++;
                    context.services[aServiceName] = Object();
                    context.services[aServiceName]['count'] = 0;
                    context.services[aServiceName]['registrationType'] = aRegistrationType;
                    context.services[aServiceName]['registrationDomain'] = aRegistrationDomain;
                }
                context.services[aServiceName]['count']++;
            } else {
                if (context.services[aServiceName])
                    context.services[aServiceName]['count']--;
                    if (context.services[aServiceName]['count'] == 0) {
                        delete context.services[aServiceName];
                        context.serviceCount--;
                    }
                }
            }
        context.setStatusBarIcon();
        }
  },
  displayStatusBarIcon: function()  {
    if (this.prefs.getBoolPref("statusbaricon")) {
        document.getElementById('bonjourStatusIcon').setAttribute("style", "display:block;");
    } else {
        document.getElementById('bonjourStatusIcon').setAttribute("style", "display:none;");
    }
  },
  setStatusBarIcon: function()   {
    var statusIcon = document.getElementById('bonjourStatusIcon');
    if (this.serviceCount == 0) {
        statusIcon.setAttribute("image", "chrome://bonjourfoxy/content/status_bw.png");
        statusIcon.setAttribute("tooltiptext", "No services discovered");
    } else {
        statusIcon.setAttribute("image", "chrome://bonjourfoxy/content/status_color.png");
        if (this.serviceCount == 1) {
            statusIcon.setAttribute("tooltiptext", this.serviceCount + " service discovered");
        } else {
            statusIcon.setAttribute("tooltiptext", this.serviceCount + " services discovered");
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
  menuAddServices: function(event)   {
    var menu = document.getElementById("bonjourMenuPopup");
    if (menu!=event.explicitOriginalTarget) return true;
    while (menu.childNodes.length>4)   {
        menu.removeChild(menu.childNodes[menu.childNodes.length-1]);
    }
    if (this.serviceCount == 0) {
        var newmenuitem = document.createElement("menuitem");
        newmenuitem.setAttribute("label", "No Services Found");
        newmenuitem.setAttribute("disabled",true);
        menu.appendChild(newmenuitem);
    } else {
        for (service in this.services)  {
            var svc = this.services[service];
            var newmenuitem = document.createElement("menuitem");
            newmenuitem.setAttribute("label", service);
            newmenuitem.setUserData("serviceName", service, null);
            newmenuitem.setUserData("registrationType", svc['registrationType'], null);
            newmenuitem.setUserData("registrationDomain", svc['registrationDomain'], null);
            newmenuitem.setAttribute("oncommand", "bonjourfoxy.menuCmdHandler(event)");
            menu.appendChild(newmenuitem);
        }
    }
  },
  menuCmdHandler: function(event) {
    var bfresolve=Components.classes["@bonjourfoxy.net/bfresolve;1"].createInstance(Components.interfaces.BFResolve);
    bfresolve.interfaceIndex=0;
    bfresolve.registrationType=event.target.getUserData("registrationType");
    bfresolve.registrationDomain=event.target.getUserData("registrationDomain");
    bfresolve.serviceName=event.target.getUserData("serviceName");
    bfresolve.callback = this.resolveCallback();
    bfresolve.resolve();
  },
  resolveCallback: function ()  {
    var prefs = Components.classes["@mozilla.org/preferences-service;1"]
                .getService(Components.interfaces.nsIPrefService);
    prefs = prefs.getBranch("extensions.bonjourfoxy.");
    linkTarget = prefs.getCharPref("target");
    return function (aError, aInterfaceIndex, aHostname, aPort, aTxtKey, aTxtValue) {
        var urltarget = linkTarget;
        if (aError) {
            var prompts = Components.classes["@mozilla.org/embedcomp/prompt-service;1"]
                        .getService(Components.interfaces.nsIPromptService);
            prompts.alert(window, "Error", "Unable to resolve service");
        } else {
            var url = "http://";
            if (aHostname.charAt(aHostname.length-1)==".")  {
                url = url + aHostname.substr(0,aHostname.length-1);
            } else {
                url = url + aHostname;
            }
            if (aPort != 80)    {
                url = url + ":" + aPort;
            }
            if (aTxtKey == "path")  {
                if (aTxtValue.charAt(0)=="/") {
                    url = url + aTxtValue;
                } else {
                    url = url + "/" + aTxtValue;
                }
            } else {
                url = url + "/";
            }
            switch (urltarget) {
                case 'tab':
                case 'window':
                    var win = Components.classes['@mozilla.org/appshell/window-mediator;1']
                        .getService(Components.interfaces.nsIWindowMediator)
                        .getMostRecentWindow('navigator:browser');
                    win.openUILinkIn(url, 'tab');
                break;
                case 'current':
                    window._content.location=url;
                break;
                default:
                    var prompts = Components.classes["@mozilla.org/embedcomp/prompt-service;1"]
                                .getService(Components.interfaces.nsIPromptService);
                    prompts.alert(window, "Error", "Bad urltarget: " + urltarget);
            }
        }
    }
}
  
};

window.addEventListener("load", function(e) { bonjourfoxy.startup(); }, false);
window.addEventListener("unload", function(e) { bonjourfoxy.shutdown(); }, false);