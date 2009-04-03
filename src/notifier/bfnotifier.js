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
            this.obsSvc = CC["@mozilla.org/observer-service;1"].getService(CI.nsIObserverService);
            this.obsSvc.addObserver(this, "profile-after-change", true);
            this.obsSvc.addObserver(this, "quit-application", true);
            break;
        
        case "profile-after-change":
            this.prefs = Components.classes["@mozilla.org/preferences-service;1"]
                .getService(Components.interfaces.nsIPrefService)
                .getBranch("extensions.bonjourfoxy.");
            this.prefs.QueryInterface(Components.interfaces.nsIPrefBranch2);
            if (this.prefs.getIntPref("rev", false)==0)  {
                var storageService = Components.classes["@mozilla.org/storage/service;1"]
                                    .getService(Components.interfaces.mozIStorageService);
                
                var dbFile = Components.classes["@mozilla.org/file/directory_service;1"]
                                .getService(Components.interfaces.nsIProperties)
                                .get("ProfD", Components.interfaces.nsIFile);
                dbFile.append("bonjourfoxy.sqlite");
                var DBConn = storageService.openDatabase(dbFile);
                var dbQueries = ['                      \
CREATE TABLE Services (                                 \
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,    \
    "regtype" TEXT,                                     \
    "scheme" TEXT,                                      \
    "label" TEXT,                                       \
    UNIQUE("regtype")                                   \
);                                                      \
    ','                                                 \
CREATE TABLE ServiceSubtypes (                          \
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,    \
    "s_id" INTEGER NOT NULL,                            \
    "subtype" TEXT,                                     \
    "label" TEXT,                                       \
    UNIQUE("id", "s_id", "subtype", "label")            \
);                                                      \
    ','                                                 \
CREATE TABLE ServicesLastInsert (                       \
    "row_id" INTEGER                                    \
);                                                      \
    ','                                                 \
INSERT INTO ServicesLastInsert values (-1);             \
    ','                                                 \
CREATE TRIGGER SST_s_id_ENFORCE                         \
BEFORE INSERT ON ServiceSubtypes                        \
FOR EACH ROW BEGIN                                      \
    SELECT RAISE(ROLLBACK, "ServiceSubtypes(s_id) must match one of Services(id)")  \
    WHERE (SELECT id FROM Services WHERE id = NEW.s_id) IS NULL;    \
END;                                                    \
    ','                                                 \
CREATE TRIGGER S_SST_CLEAN                              \
BEFORE DELETE ON Services                               \
FOR EACH ROW BEGIN                                      \
    DELETE from ServiceSubtypes WHERE s_id = OLD.id;    \
END;                                                    \
    ','                                                 \
INSERT INTO Services (regtype, scheme, label)           \
VALUES (                                                \
    "_http._tcp.",                                      \
    "http://${iftxtvalue:u:${txtvalue:u}}${iftxtvalue:u:${iftxtvalue:p::${txtvalue:p}}}${iftxtvalue:u:@}${srv:hostname}:${srv:port}${ifnxtcharsne:/:/}${txtvalue:path}",    \
    "Websites"                                          \
    );                                                  \
    ','                                                 \
INSERT INTO ServiceSubtypes (s_id, subtype, label)      \
VALUES (1, "_wiki", "Wikis");                           \
    ','                                                 \
INSERT INTO ServiceSubtypes (s_id, subtype, label)      \
VALUES (1, "_printer", "Printers");                     \
    '];
                for (i=0;i<dbQueries.length;i++)    {
                    try { DBConn.executeSimpleSQL(dbQueries[i]); }
                    catch (e)   {
                        dump (['Error executing dbQueries['+i+']',DBConn.lastError,DBConn.lastErrorString,"\n"].join(' '));
                        break;
                    }
                }
            }
            this.prefs.addObserver("", this, false);
            this.displayAlerts = this.prefs.getBoolPref("alerts");
            this.dsdManager=Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
            this.alertsService = Components.classes["@mozilla.org/alerts-service;1"].getService(Components.interfaces.nsIAlertsService);
            this.setHandlers();
        break;
        
        case "profile-before-change":
            this.removeHandlerObservers();
            this.prefs.removeObserver("", this);
            this.dsdManager = null;
            this.alertsService = null;
            this.handlers = {};
        break;
        
        case "nsPref:changed":
            switch (aData)   {
                case "hts":
                    this.setHandlers();
                break;
                case "alerts":
                    this.displayAlerts = this.prefs.getBoolPref("alerts");
                break;
            }
        break;
        
        default:
             if (aTopic.match(/^dsd_service_add/))   {
                 var newType = aTopic.split(":")[1];
                 if (this.handlers[newType])
                 {
                     if (this.displayAlerts)
                     {
                        var serviceInfo = this.dsdManager.getServiceInfoFromId(aData);
                        var serviceName = serviceInfo.queryElementAt(0, Components.interfaces.nsIVariant);
                        var regType = serviceInfo.queryElementAt(1, Components.interfaces.nsIVariant);
                        var regSubTypes = serviceInfo.queryElementAt(3, Components.interfaces.nsIVariant);
                        var regDomain = serviceInfo.queryElementAt(2, Components.interfaces.nsIVariant);
                        if (this.dsdManager.getServiceNameCount(serviceName)==1)  {
                            this.alertsService.showAlertNotification(null,"Service Discovered",serviceName,null,null,null);
                        }
                     }
                 }
            }
        }
    },
    handlers: {},
    removeHandlerObservers: function()  {
        for (property in this.handlers) {
            this.obsSvc.removeObserver(this, "dsd_service_add:" + property, false);
        }
    },
    addHandlerObservers: function() {
        for (property in this.handlers) {
            this.obsSvc.addObserver(this, "dsd_service_add:" + property, false);
        }
    },
    setHandlers: function() {
        this.removeHandlerObservers();
        var storageService = Components.classes["@mozilla.org/storage/service;1"]
                        .getService(Components.interfaces.mozIStorageService);        
        var dbFile = Components.classes["@mozilla.org/file/directory_service;1"]
                        .getService(Components.interfaces.nsIProperties)
                        .get("ProfD", Components.interfaces.nsIFile);
        dbFile.append("bonjourfoxy.sqlite");
        var DBConn = storageService.openDatabase(dbFile);
        var sqlGetRegTypes = DBConn.createStatement("                   \
SELECT                                                                  \
    Services.regtype as regtype,                                        \
    Services.label as label,                                            \
    GROUP_CONCAT(DISTINCT ServiceSubtypes.subtype) as subtypes          \
FROM Services                                                           \
LEFT OUTER JOIN ServiceSubtypes ON Services.id = ServiceSubtypes.s_id   \
GROUP BY Services.regtype, Services.scheme, Services.label;             ");
        var newHandlers = {};
        var regtypeSearches = [];
        while(sqlGetRegTypes.executeStep()) {
            var regType = sqlGetRegTypes.getUTF8String(0);
            var label = sqlGetRegTypes.getUTF8String(1);
            try { var subRegtypes = sqlGetRegTypes.getUTF8String(2).split(','); }
            catch (e) { var subRegtypes = []; }
            newHandlers[regType] = label;
            regtypeSearches.push(regType);
            for (var i=0;i<subRegtypes.length;i++)  {
                regtypeSearches.push([regType,subRegtypes[i]].join(','));
            }
        }
        while(regType=regtypeSearches.pop())    {
            this.dsdManager.discoverServices(regType,null);
        }
        
        this.handlers = newHandlers;
        this.addHandlerObservers();
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
