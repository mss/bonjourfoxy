BFNotifierServiceRefs = Object()
function BFNotifier() {
// you can do |this.wrappedJSObject = this;| for the first version of the component
// (in case you don't want to write IDL yet.)
}
BFNotifier.prototype = {
    classID: Components.ID("2a0884a8-40d8-4e12-afd6-26530b2e47c2"), // xxx generate guid
    contractID: "@andrew.tj.id.au/bfnotifier;1", // XXX generated contractid too
    classDescription: "BFNotifier",

    QueryInterface: function(aIID) {
    if(!aIID.equals(CI.nsISupports) && !aIID.equals(CI.nsIObserver) && !aIID.equals(CI.nsISupportsWeakReference)) // you can claim you implement more interfaces here
        throw CR.NS_ERROR_NO_INTERFACE;
    return this;
    },
    serviceRefs: Object(),
    browseCallback: function(aError, aAdd, aInterfaceIndex, aServiceName, aRegistrationType, aRegistrationDomain) {
        var info = ( [aError, aAdd, aInterfaceIndex, aServiceName, aRegistrationType, aRegistrationDomain].join(" ") );
        if (!aError)    {
            if (aAdd) {
                if (!BFNotifierServiceRefs[aServiceName]) {
                    BFNotifierServiceRefs[aServiceName] = 0;
                }
                BFNotifierServiceRefs[aServiceName]++;
                if (BFNotifierServiceRefs[aServiceName]==1) {
                    var prefs = Components.classes["@mozilla.org/preferences-service;1"]
                        .getService(Components.interfaces.nsIPrefService)
                        .getBranch("extensions.bonjourfoxy.");
                    var displayAlert = prefs.getBoolPref("alerts");
                    if (displayAlert) {
                        var alerts = Components.classes["@mozilla.org/alerts-service;1"]
                            .getService(Components.interfaces.nsIAlertsService);
                        alerts.showAlertNotification(null, 'Service Discovered', aServiceName, null, null, null);
                    }
                }
            } else {
                BFNotifierServiceRefs[aServiceName]--;
            }
        }
    },
    observe: function(aSubject, aTopic, aData) {
    switch(aTopic) {
        case "xpcom-startup":
            // this is run very early, right after XPCOM is initialized, but before
            // user profile information is applied. Register ourselves as an observer
            // for 'profile-after-change' and 'quit-application'.
            this.obsSvc = CC["@mozilla.org/observer-service;1"].getService(CI.nsIObserverService);
            this.obsSvc.addObserver(this, "profile-after-change", true);
            this.obsSvc.addObserver(this, "quit-application", true);
            break;
        
        case "profile-after-change":
            this.bfbrowse = Components.classes["@bonjourfoxy.net/bfbrowse;1"]
                .createInstance(Components.interfaces.BFBrowse);
            this.bfbrowse.callback=this.browseCallback;
            this.bfbrowse.interfaceIndex=0;
            this.bfbrowse.registrationType="_http._tcp";
            this.bfbrowse.registrationDomain="local.";
            this.bfbrowse.browse();
        break;
        
        case "profile-before-change":
            this.bfbrowse = null;
        break;        
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
