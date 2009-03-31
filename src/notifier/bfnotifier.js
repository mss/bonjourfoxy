function BFNotifier() {
// you can do |this.wrappedJSObject = this;| for the first version of the component
// (in case you don't want to write IDL yet.)
}
BFNotifier.prototype = {
    classID: Components.ID("2a0884a8-40d8-4e12-afd6-26530b2e47c2"), // xxx generate guid
    contractID: "@andrew.tj.id.au/bfnotifier;1", // XXX generated contractid too
    classDescription: "BFNOTIFIER",

    QueryInterface: function(aIID) {
    if(!aIID.equals(CI.nsISupports) && !aIID.equals(CI.nsIObserver) && !aIID.equals(CI.nsISupportsWeakReference)) // you can claim you implement more interfaces here
        throw CR.NS_ERROR_NO_INTERFACE;
    return this;
    },
    // nsIObserver implementation
    observe: function(aSubject, aTopic, aData) {
    switch(aTopic) {
        case "xpcom-startup":
            // this is run very early, right after XPCOM is initialized, but before
            // user profile information is applied. Register ourselves as an observer
            // for 'profile-after-change' and 'quit-application'.
            var obsSvc = CC["@mozilla.org/observer-service;1"].getService(CI.nsIObserverService);
            obsSvc.addObserver(this, "profile-after-change", true);
            obsSvc.addObserver(this, "quit-application", true);
            break;
        
        case "profile-after-change":
            var observerService = Components.classes["@mozilla.org/observer-service;1"]
                          .getService(Components.interfaces.nsIObserverService);
            observerService.addObserver(this, "dsd_service_add__http._tcp.", false);
        break;
        
        case "profile-before-change":
            var observerService = Components.classes["@mozilla.org/observer-service;1"]
                                    .getService(Components.interfaces.nsIObserverService);
            observerService.removeObserver(this, "dsd_service_add__http._tcp.", false);
        break;
        
        default:
             if (aTopic=="dsd_service_add__http._tcp.")
             {
                 var dsdManager=Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
                 var prefs = Components.classes["@mozilla.org/preferences-service;1"].getService(Components.interfaces.nsIPrefService);
                 prefs = prefs.getBranch("extensions.bonjourfoxy.");
                 if (prefs.getBoolPref("alerts"))
                 {
                     // kludgey....
                     if (dsdManager.getServiceNameCount(aData)==1)  {
                         var alertsService = Components.classes["@mozilla.org/alerts-service;1"].getService(Components.interfaces.nsIAlertsService);
                         alertsService.showAlertNotification(null,"Service Discovered",aData,null,null,null);
                     }
                 }
             }
        }
    }
};


// constructors for objects we want to XPCOMify
var objects = [BFNotifier];

/*
* Registration code.
*
*/

const CI = Components.interfaces, CC = Components.classes, CR = Components.results;

const MY_OBSERVER_NAME = "BFNOTIFIER OBSERVER";

function FactoryHolder(aObj) {
    this.CID        = aObj.prototype.classID;
    this.contractID = aObj.prototype.contractID;
    this.className  = aObj.prototype.classDescription;
    this.factory = {
    createInstance: function(aOuter, aIID) {
        if(aOuter)
        throw CR.NS_ERROR_NO_AGGREGATION;
        return (new this.constructor).QueryInterface(aIID);
    }
    };
    this.factory.constructor = aObj;
}

var gModule = {
    registerSelf: function (aComponentManager, aFileSpec, aLocation, aType)
    {
    aComponentManager.QueryInterface(CI.nsIComponentRegistrar);
    for (var key in this._objects) {
        var obj = this._objects[key];
        aComponentManager.registerFactoryLocation(obj.CID, obj.className,
        obj.contractID, aFileSpec, aLocation, aType);
    }

    // this can be deleted if you don't need to init on startup
    var catman = CC["@mozilla.org/categorymanager;1"].getService(CI.nsICategoryManager);
    catman.addCategoryEntry("xpcom-startup", MY_OBSERVER_NAME,
        BFNotifier.prototype.contractID, true, true);
    catman.addCategoryEntry("xpcom-shutdown", MY_OBSERVER_NAME,
        BFNotifier.prototype.contractID, true, true);
    },

    unregisterSelf: function(aCompMgr, aFileSpec, aLocation) {
    // this must be deleted if you delete the above code dealing with |catman|
    var catman = CC["@mozilla.org/categorymanager;1"].getService(CI.nsICategoryManager);
    catman.deleteCategoryEntry("xpcom-startup", MY_OBSERVER_NAME, true);
    // end of deleteable code

    aComponentManager.QueryInterface(CI.nsIComponentRegistrar);
    for (var key in this._objects) {
        var obj = this._objects[key];
        aComponentManager.unregisterFactoryLocation(obj.CID, aFileSpec);
    }
    },

    getClassObject: function(aComponentManager, aCID, aIID) {
    if (!aIID.equals(CI.nsIFactory)) throw CR.NS_ERROR_NOT_IMPLEMENTED;

    for (var key in this._objects) {
        if (aCID.equals(this._objects[key].CID))
        return this._objects[key].factory;
    }
    
    throw CR.NS_ERROR_NO_INTERFACE;
    },

    canUnload: function(aComponentManager) {
    return true;
    },

    _objects: {} //FactoryHolder
};

function NSGetModule(compMgr, fileSpec)
{
    for(var i in objects)
    gModule._objects[i] = new FactoryHolder(objects[i]);
    return gModule;
}
