const nsISupports = Components.interfaces.nsISupports;
const IDSDMANAGER = Components.interfaces.IDSDMANAGER;

// You can change these if you like
const CLASS_ID = Components.ID("2a4a57ac-0b06-4fdc-aa3a-f8e4e9195f50");
const CLASS_NAME = "DSDMANAGER";
const CONTRACT_ID = "@andrew.tj.id.au/dsdmanager;1";

// This is your constructor.
// You can do stuff here.
function DSDMANAGER() {
  // you can cheat and use this
  // while testing without
  // writing your own interface
  this.wrappedJSObject = this;
  this.storageService = Components.classes["@mozilla.org/storage/service;1"]
                        .getService(Components.interfaces.mozIStorageService);
  /*
  this.dbFile = Components.classes["@mozilla.org/file/directory_service;1"]
                    .getService(Components.interfaces.nsIProperties)
                    .get("ProfD", Components.interfaces.nsIFile);
  this.dbFile.append("testdb.sqlite");
  this.DBConn = this.storageService.openDatabase(this.dbFile);
  */
  this.DBConn = this.storageService.openDatabase(null);
  this.DBConn.executeSimpleSQL('                                            \
CREATE TABLE DiscoveredDomains (                                            \
    "id" integer not null primary key autoincrement,                        \
    "regdomain" text,                                                       \
    "domaintype" text,                                                      \
    "ifindex" integer,                                                      \
    UNIQUE("regdomain", "domaintype", "ifindex")                            \
);                                                                          \
                                                                            \
CREATE TABLE DiscoveredServices (                                           \
    "id" integer primary key autoincrement,                                 \
    "regdomain" text,                                                       \
    "regtype" text,                                                         \
    "servicename" text,                                                     \
    "ifindex" integer,                                                      \
    UNIQUE ("regdomain", "regtype", "servicename", "ifindex")               \
);                                                                          \
                                                                            \
CREATE TABLE DiscoveredServicesSubTypes (                                   \
    "id" integer not null primary key autoincrement,                        \
    "ds_id" integer not null,                                               \
    "subtype" text                                                          \
);                                                                          \
                                                                            \
CREATE TRIGGER DSST_ds_id_ENFORCE                                           \
BEFORE INSERT ON DiscoveredServicesSubTypes                                 \
FOR EACH ROW BEGIN                                                          \
    SELECT RAISE(ROLLBACK, "DSST(ds_id) must match one of DS(id)")          \
    WHERE  (SELECT id FROM DiscoveredServices WHERE id = NEW.ds_id) IS NULL;\
END;                                                                        \
                                                                            \
CREATE TRIGGER DS_DSST_CLEAN                                                \
BEFORE DELETE ON DiscoveredServices                                         \
FOR EACH ROW BEGIN                                                          \
    DELETE from DiscoveredServicesSubTypes WHERE ds_id = OLD.id;            \
END;                                                                        ');
  this.BrowseEnumerateInstance=Components.classes["@andrew.tj.id.au/dsdenumerate;1"].createInstance(Components.interfaces.IDSDENUMERATE);
  this.BrowseEnumerateInstance.type=1;
  this.BrowseEnumerateInstance.interfaceIndex=0;
  this.BrowseEnumerateInstance.start();
  this.RegistrationEnumerateInstance=Components.classes["@andrew.tj.id.au/dsdenumerate;1"].createInstance(Components.interfaces.IDSDENUMERATE);
  this.RegistrationEnumerateInstance.type=2;
  this.RegistrationEnumerateInstance.interfaceIndex=0;
  this.RegistrationEnumerateInstance.start();
}

// This is the implementation of your component.
DSDMANAGER.prototype = {
  log: function(message)   {
    var prefs = Components.classes["@mozilla.org/preferences-service;1"]
                    .getService(Components.interfaces.nsIPrefService);
    prefs = prefs.getBranch("extensions.dsd.");
    if (prefs.getBoolPref("logToErrorConsole"))  {
        var aConsoleService = Components.classes["@mozilla.org/consoleservice;1"].getService(Components.interfaces.nsIConsoleService);
        aConsoleService.logStringMessage(message);
    }
  },
  validServiceName: function(input) {
    var escapedStr = encodeURI(input)
    if (escapedStr.indexOf("%") != -1) {
        var count = escapedStr.split("%").length - 1
        if (count == 0) count++
        var tmp = escapedStr.length - (count * 3)
        count = count + tmp
    } else {
        count = escapedStr.length
    }
    if (count>63)   {
        return false;
    } else {
        return true;
    }
  },
  validRegistrationType: function(input)   {
    if (input=="_services._dns-sd._udp.") {
        return true; 
    }
    var expression = "^(_[a-zA-Z0-9\-]{1,14}\.)_(ud|tc)p\.(\,_[a-zA-Z0-9\-]{1,14})*$";
    var re = new RegExp(expression);
    if (input.match(re))  {
        return true;
        } else {
        return false;
    }
  },
  BrowseInstances: Object(),
  discoverServices: function(regType,regDomain)
  {
    if (!this.validRegistrationType(regType))   {
        return false;
    }
    var invocationTxt = "discoverServices(" + Array.prototype.slice.call(arguments).join(",") + ")";
    this.log(invocationTxt);
    if (null==regDomain)
    {
        if (!this.BrowseInstances[regType])
        {
            this.BrowseInstances[regType] = Components.classes["@andrew.tj.id.au/dsdbrowse;1"].createInstance(Components.interfaces.IDSDBROWSE);
            this.BrowseInstances[regType].interfaceIndex=0;
            this.BrowseInstances[regType].registrationType=regType;
            this.BrowseInstances[regType].registrationDomain=null;
            this.BrowseInstances[regType].start();
        }    
    } 
    else
    {
        if (!this.BrowseInstances[regDomain]) this.BrowseInstances[regDomain] = Object();
        if (!this.BrowseInstances[regDomain][regType])
        {
            this.BrowseInstances[regDomain][regType] = Components.classes["@andrew.tj.id.au/dsdbrowse;1"].createInstance(Components.interfaces.IDSDBROWSE);
            this.BrowseInstances[regDomain][regType].interfaceIndex=0;
            this.BrowseInstances[regDomain][regType].registrationType=regType;
            this.BrowseInstances[regDomain][regType].registrationDomain=regDomain;
            this.BrowseInstances[regDomain][regType].start();
        }
    }                
    return true;
  },
  getDiscoveredDomains: function(domainType)
  {
    var invocationTxt = "getDiscoveredDomains(" + Array.prototype.slice.call(arguments).join(",") + ")";
    this.log(invocationTxt);
    var arrayDiscoveredDomains = Components.classes["@mozilla.org/array;1"].createInstance(Components.interfaces.nsIMutableArray);
    if (domainType == null)
    {
        var sqlDiscoveredDomains = this.DBConn.createStatement("SELECT * FROM DiscoveredDomains GROUP BY regdomain, domaintype");
    }
    else
    {
        var sqlDiscoveredDomains = this.DBConn.createStatement("SELECT * FROM DiscoveredDomains WHERE domaintype=?1 GROUP BY regdomain, domaintype");        
        sqlDiscoveredDomains.bindUTF8StringParameter(0, domainType);
    }
    while(sqlDiscoveredDomains.executeStep())
    {
        var arrayDiscoveredDomain = Components.classes["@mozilla.org/array;1"].createInstance(Components.interfaces.nsIMutableArray);
        var regDomain = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
        regDomain.setFromVariant(sqlDiscoveredDomains.getUTF8String(0));
        arrayDiscoveredDomain.appendElement(regDomain, 0);
        var domainType = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
        domainType.setFromVariant(sqlDiscoveredDomains.getUTF8String(1));
        arrayDiscoveredDomain.appendElement(domainType, 0);
        arrayDiscoveredDomains.appendElement(arrayDiscoveredDomain, 0);
    }
    return arrayDiscoveredDomains;
  },
  getDiscoveredDomainsCount: function(domainType)
  {
    var invocationTxt = "getDiscoveredDomainsCount(" + Array.prototype.slice.call(arguments).join(",") + ")";
    this.log(invocationTxt);
    var count=0;
    var sqlCountDiscoveredDomains = null;
    if (domainType == null)
    {
        sqlCountDiscoveredDomains = this.DBConn.createStatement("SELECT COUNT(1) FROM DiscoveredDomains GROUP BY regdomain, domaintype");
    }
    else
    {
        sqlCountDiscoveredDomains = this.DBConn.createStatement("SELECT COUNT(1) FROM DiscoveredDomains WHERE domaintype=?1 GROUP BY regdomain, domaintype");
        sqlCountDiscoveredDomains.bindUTF8StringParameter(0, domainType);
    }
    /* there's gotta be a better way... */
    while (sqlCountDiscoveredDomains.executeStep())
    {
        count++;
    }
    this.log([invocationTxt,"returning:",count].join(" "));
    return count;
  },  
  getDiscoveredServices: function (regType, regDomain)
  {
    var invocationTxt = "getDiscoveredServices(" + Array.prototype.slice.call(arguments).join(",") + ")";
    this.log(invocationTxt);
    var arrayDiscoveredServices = Components.classes["@mozilla.org/array;1"].createInstance(Components.interfaces.nsIMutableArray);
    var sqlSubTypes = regType.indexOf(',')!=-1;
    var sqlSubTypesQuery = "";
    var subTypesArray = [];
    if (sqlSubTypes)
    {
        var subTypesArray = regType.split(',');
        regType = subTypesArray[0];
        for (i=1;i<subTypesArray.length;i++)
        {
            this.log([i+2,subTypesArray[i]].join(' '));
            sqlSubTypesQuery += " AND DiscoveredServicesSubtypes.subtype = ?" + (i+2);
        }
    }
    var sqlDiscoveredServices = this.DBConn.createStatement("   \
SELECT                                                          \
    DiscoveredServices.regdomain as regdomain,                  \
    DiscoveredServices.regtype as regtype,                      \
    DiscoveredServices.servicename as servicename,              \
    DiscoveredServices.id as service_id,                        \
    GROUP_CONCAT(                                               \
        DISTINCT DiscoveredServicesSubtypes.subtype             \
    ) AS subtypes                                               \
FROM DiscoveredServices                                         \
LEFT OUTER JOIN DiscoveredServicesSubTypes                      \
ON DiscoveredServices.id = DiscoveredServicesSubtypes.ds_id     \
WHERE DiscoveredServices.regtype = ?1                           \
"   + ( (regDomain==null) ? "" : " AND regdomain = ?2" ) + "    \
"   + ( (sqlSubTypes) ? sqlSubTypesQuery  : '' ) + "            \
GROUP BY                                                        \
    DiscoveredServices.regdomain,                               \
    DiscoveredServices.regtype,                                 \
    DiscoveredServices.servicename                             ");
    sqlDiscoveredServices.bindUTF8StringParameter(0, regType);
    if (regDomain)
    {
        sqlDiscoveredServices.bindUTF8StringParameter(1, regDomain);
    }
    if (sqlSubTypes)
    {
        for (i=1;i<subTypesArray.length;i++)
        {
            this.log([i,i+1,subTypesArray[i]].join(''));
            sqlDiscoveredServices.bindUTF8StringParameter(i+1, subTypesArray[i]);
        }
    }
    while (sqlDiscoveredServices.executeStep())
    {
      var arrayDiscoveredService = Components.classes["@mozilla.org/array;1"].createInstance(Components.interfaces.nsIMutableArray);
      var regDomain = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
      regDomain.setFromVariant(sqlDiscoveredServices.getUTF8String(0));
      arrayDiscoveredService.appendElement(regDomain, 0);
      var regType = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
      regType.setFromVariant(sqlDiscoveredServices.getUTF8String(1));
      arrayDiscoveredService.appendElement(regType, 0);
      var serviceName = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
      serviceName.setFromVariant(sqlDiscoveredServices.getUTF8String(2));
      arrayDiscoveredService.appendElement(serviceName, 0);
      var serviceId = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
      serviceId.setFromVariant(sqlDiscoveredServices.getUTF8String(3));
      arrayDiscoveredService.appendElement(serviceId, 0);
      var subTypes = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
      subTypes.setFromVariant(sqlDiscoveredServices.getUTF8String(4));
      arrayDiscoveredService.appendElement(subTypes, 0);
      arrayDiscoveredServices.appendElement(arrayDiscoveredService, 0);
    }
    return arrayDiscoveredServices;
  },
  getDiscoveredServicesCount: function(regType, regDomain)
  {
    var invocationTxt = "getDiscoveredServicesCount(" + Array.prototype.slice.call(arguments).join(",") + ")";
    this.log(invocationTxt);
    var count=0;
    var sqlCountDiscoveredServices = null;
    if (regDomain==null)    {
        sqlCountDiscoveredServices = this.DBConn.createStatement("SELECT COUNT(1) FROM DiscoveredServices WHERE regtype = ?1 GROUP BY regdomain, regtype, servicename");
    } else {
        sqlCountDiscoveredServices = this.DBConn.createStatement("SELECT COUNT(1) FROM DiscoveredServices WHERE regtype = ?1 AND regdomain = ?2 GROUP BY regdomain, regtype, servicename");
        sqlCountDiscoveredServices.bindUTF8StringParameter(1, regDomain);
    }
    sqlCountDiscoveredServices.bindUTF8StringParameter(0, regType);
    while (sqlCountDiscoveredServices.executeStep()) {
        count++;
    }
    this.log([invocationTxt,"returning:",count].join(" "));
    return count;
  },
  getServiceNameCount: function(serviceName)
  {
    var invocationTxt = "getServiceNameCount(" + Array.prototype.slice.call(arguments).join(",") + ")";
    this.log(invocationTxt);
    var count=0;
    var sqlServiceNameCount = this.DBConn.createStatement("SELECT COUNT(1) FROM DiscoveredServices WHERE servicename = ?1");
    sqlServiceNameCount.bindUTF8StringParameter(0, serviceName);
    while (sqlServiceNameCount.executeStep()) {
        count = sqlServiceNameCount.getInt32(0);
    }
    this.log([invocationTxt,"returning:",count].join(" "));
    return count;
  },
  ResolverInstances: Object(),
  ResolverInstance: function()
  {
      var now = new Date();
      this.initTS=Math.round(now.getTime()/1000.0);
      this.stopTS=-1;
      this.obj=Components.classes["@andrew.tj.id.au/dsdresolve;1"].createInstance(Components.interfaces.IDSDRESOLVE);
      this.obj.interfaceIndex=0;
      this.timeout=5;
      this.targetHostname="";
      this.targetPort="";
      this.txtRecords=Array();
      return this;
  },
  getServiceInfoFromId: function(serviceId)
  {
    var returnArray = Components.classes["@mozilla.org/array;1"].createInstance(Components.interfaces.nsIMutableArray);
    var serviceName = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
    var regType = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
    var regDomain = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
    var subRegTypes = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
    var sqlGetServiceDetails = this.DBConn.createStatement("                \
SELECT                                                                      \
    DiscoveredServices.servicename as servicename,                          \
    DiscoveredServices.regtype as regtype,                                  \
    DiscoveredServices.regdomain as regdomain,                              \
    GROUP_CONCAT(DISTINCT DiscoveredServicesSubtypes.subtype) AS subtypes   \
FROM DiscoveredServices                                                     \
LEFT OUTER JOIN DiscoveredServicesSubTypes                                  \
ON DiscoveredServices.id = DiscoveredServicesSubtypes.ds_id                 \
WHERE DiscoveredServices.id = ?1                                            \
GROUP BY                                                                    \
    DiscoveredServices.regdomain,                                           \
    DiscoveredServices.regtype,                                             \
    DiscoveredServices.servicename,                                         \
    DiscoveredServicesSubtypes.subtype                                      ");
    sqlGetServiceDetails.bindInt32Parameter(0,serviceId);
    while (sqlGetServiceDetails.executeStep())  {
        serviceName.setFromVariant(sqlGetServiceDetails.getUTF8String(0));
        regType.setFromVariant(sqlGetServiceDetails.getUTF8String(1));
        regDomain.setFromVariant(sqlGetServiceDetails.getUTF8String(2));        
        subRegTypes.setFromVariant(sqlGetServiceDetails.getUTF8String(3));        
    }
    sqlGetServiceDetails.reset();
    returnArray.appendElement(serviceName, 0);
    returnArray.appendElement(regType, 0);
    returnArray.appendElement(regDomain, 0);
    returnArray.appendElement(subRegTypes, 0);
    return returnArray;
  },
  resolveServiceFromId: function(serviceId)
  {
    var serviceInfo = this.getServiceInfoFromId(serviceId);
    return this.resolveService(
        serviceInfo.queryElementAt(0,Components.interfaces.nsIVariant),
        serviceInfo.queryElementAt(1,Components.interfaces.nsIVariant),
        serviceInfo.queryElementAt(2,Components.interfaces.nsIVariant));
  },  
  resolveService: function(serviceName,regType,regDomain)
  {
    var invocationTxt = "resolveServices(" + Array.prototype.slice.call(arguments).join(",") + ")";
    this.log(invocationTxt);
    var now = new Date();
    var returnArray = Components.classes["@mozilla.org/array;1"].createInstance(Components.interfaces.nsIMutableArray);
    var returnCode = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
    var returnPayload = Components.classes["@mozilla.org/array;1"].createInstance(Components.interfaces.nsIMutableArray);
    var id = serviceName + "." + regType + regDomain;
    if (!this.ResolverInstances[id])
    {
        this.ResolverInstances[id] = new this.ResolverInstance();
        this.ResolverInstances[id].obj.name = serviceName;
        this.ResolverInstances[id].obj.registrationType = regType;
        this.ResolverInstances[id].obj.registrationDomain = regDomain;
        this.log(invocationTxt + ": instance created");
    }
    switch(this.ResolverInstances[id].obj.status)
    {
        case 0:
            this.ResolverInstances[id].obj.start();
            this.ResolverInstances[id].startTS=Math.round(now.getTime()/1000.0);
            this.log(invocationTxt + ": instance started");
        case 1:
            returnCode.setFromVariant("0");
            this.log(invocationTxt + ": instance running");
        break;
        case 2:
            var instanceAge = Math.round(now.getTime()/1000.0) - this.ResolverInstances[id].stopTS;
            if ( instanceAge > 14 )  { // arbitrary
                this.ResolverInstances[id]=null;
                returnCode.setFromVariant("0");
                this.log([invocationTxt,": instance destroyed (",instanceAge,")"].join(''));
            } else {
                returnCode.setFromVariant("1");
                var targetHostname = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
                targetHostname.setFromVariant(this.ResolverInstances[id].targetHostname);
                returnPayload.appendElement(targetHostname, 0);
                var targetPort = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
                targetPort.setFromVariant(this.ResolverInstances[id].targetPort);
                returnPayload.appendElement(targetPort, 0);
                returnPayload.appendElement(this.ResolverInstances[id].txtRecords, 0);
                this.log(invocationTxt + ": instance has data");
            }
        break;
        default:
            returnCode.setFromVariant("-1");
            var lastErrorcode = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
            lastErrorcode.setFromVariant(this.ResolverInstances[id].lastErrorCode);
            returnPayload.appendElement(lastErrorcode, 0);
            this.ResolverInstances[id]=null;
            this.log([invocationTxt,": instance fatal state -",this.ResolverInstances[id].obj.status].join(''))
    }
    returnArray.appendElement(returnCode,0);
    returnArray.appendElement(returnPayload,0);
    this.log([invocationTxt,"returning",returnArray.length,"args"].join(" "));
    return returnArray;
  },
  RegistrationInstances: Object(),
  addService: function(serviceName, regType, targetHost, targetPort, txtKey, txtValue, regDomain)   {
    var invocationTxt = "addService(" + Array.prototype.slice.call(arguments).join(",") + ")";
    this.log(invocationTxt);
    if (!this.validServiceName(serviceName) || !this.validRegistrationType(regType))
    {
        return;
    }
    var CHARS = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'.split('');
    var chars = CHARS, uuid = [], rnd = Math.random;
    for (var i = 0; i < 15; i++) uuid[i] = chars[0 | rnd()*chars.length];
    var id = uuid.join('');
    this.RegistrationInstances[id] = Components.classes["@andrew.tj.id.au/dsdregister;1"].createInstance(Components.interfaces.IDSDREGISTER);
    this.RegistrationInstances[id].instanceId = id;
    this.RegistrationInstances[id].interfaceIndex=0;
    this.RegistrationInstances[id].autorename = true;
    this.RegistrationInstances[id].name = serviceName;
    this.RegistrationInstances[id].registrationType = regType;
    this.RegistrationInstances[id].registrationDomain = regDomain;
    this.RegistrationInstances[id].targetHost = targetHost;
    this.RegistrationInstances[id].targetPort = targetPort;
    this.RegistrationInstances[id].txtRecordKey = txtKey;
    this.RegistrationInstances[id].txtRecordValue = txtValue;
    try { this.RegistrationInstances[id].start(); }
    catch (e)
    {
        this.RegistrationInstances[id]=null;
        return;
    }
    this.log([invocationTxt,"returning:",id].join(" "));
    return id;
  },
  removeService: function(identifier)
  {
    var invocationTxt = "removeService(" + Array.prototype.slice.call(arguments).join(",") + ")";
    this.log(invocationTxt);
    if (this.RegistrationInstances[identifier])
    {
        this.RegistrationInstances[identifier].stop();
        this.RegistrationInstances[identifier]=null;
        delete this.RegistrationInstances[identifier];
    }
  },    
  handleEvent: function(from,isError,data)
  {
    var invocationTxt = "handleEvent(" + Array.prototype.slice.call(arguments).join(",") + ")";
    this.log(invocationTxt);
    var observerService = Components.classes["@mozilla.org/observer-service;1"].getService(Components.interfaces.nsIObserverService);
    switch(from)
        {
        case "enumerate":
            if (!isError)
            {
                flags = data.queryElementAt(0,Components.interfaces.nsIVariant);
                if (flags == 'add')
                {
                    var sql = this.DBConn.createStatement("INSERT INTO DiscoveredDomains (regdomain, domaintype, ifindex) VALUES (?1, ?2, ?3)");
                } else {
                    var sql = this.DBConn.createStatement("DELETE FROM DiscoveredDomains WHERE regdomain = ?1 AND domaintype = ?2 AND ifindex = ?3");
                }
                var interfaceIndex = data.queryElementAt(2,Components.interfaces.nsIVariant);
                sql.bindInt32Parameter(2, interfaceIndex);
                var regDomain = data.queryElementAt(3,Components.interfaces.nsIVariant);
                sql.bindUTF8StringParameter(0, regDomain);
                var domainType = data.queryElementAt(1,Components.interfaces.nsIVariant); 
                sql.bindUTF8StringParameter(1, domainType);
                sql.execute();
                sql.reset();
                // below should look like for eg: "dsd_domain_add:registration"
                observerService.notifyObservers(null, ["dsd_domain_",flags,':',domainType].join(""), regDomain);
            }
        break;
        case "browse":
            if (!isError)
            {
                var notify = true;
                flags = data.queryElementAt(0,Components.interfaces.nsIVariant);
                if (flags == "add")
                {
                    var sql = this.DBConn.createStatement("INSERT INTO DiscoveredServices (regdomain, regtype, servicename, ifindex) VALUES (?1, ?2, ?3, ?4)");
                } else {
                    var sql = this.DBConn.createStatement("DELETE FROM DiscoveredServices WHERE regdomain = ?1 AND regtype = ?2 AND servicename = ?3 AND ifindex = ?4");
                }
                var requestedRegType = data.queryElementAt(5, Components.interfaces.nsIVariant);
                var hasSubTypes = requestedRegType.indexOf(',')!=-1;
                var regDomain = data.queryElementAt(4, Components.interfaces.nsIVariant);
                sql.bindUTF8StringParameter(0, regDomain);
                var regType = data.queryElementAt(3, Components.interfaces.nsIVariant);
                sql.bindUTF8StringParameter(1, regType);
                var serviceName = data.queryElementAt(2, Components.interfaces.nsIVariant);
                sql.bindUTF8StringParameter(2, serviceName);
                var interfaceIndex = data.queryElementAt(1, Components.interfaces.nsIVariant);
                sql.bindInt32Parameter(3, interfaceIndex);
                try { sql.execute(); }
                catch (e if this.DBConn.lastError == 19)
                {
                    notify = false;
                    this.log("DiscoveredServices already contains a record for ['" + [regDomain,regType,serviceName,interfaceIndex].join("','") + "']");
                }
                sql.reset();
                var sqlServiceID = this.DBConn.createStatement("SELECT id FROM DiscoveredServices WHERE regdomain = ?1 AND regtype = ?2 AND servicename =?3 AND ifindex = ?4");
                sqlServiceID.bindUTF8StringParameter(0, regDomain);
                sqlServiceID.bindUTF8StringParameter(1, regType);
                sqlServiceID.bindUTF8StringParameter(2, serviceName);
                sqlServiceID.bindInt32Parameter(3, interfaceIndex);
                var serviceID = null;
                while (sqlServiceID.executeStep()) {
                    serviceID = sqlServiceID.getInt32(0);
                }
                if (notify) { observerService.notifyObservers(null, ["dsd_service_",flags,':',regType].join(""), serviceID); }
                if (flags == "add" && hasSubTypes)
                {
                    var subTypesArray = requestedRegType.split(",");
                    var sqlInsertSubTypes = this.DBConn.createStatement("INSERT INTO DiscoveredServicesSubTypes (ds_id, subtype) VALUES (?1, ?2)");
                    for (i=1;i<subTypesArray.length;i++)
                    {
                        sqlInsertSubTypes.bindInt32Parameter(0, serviceID);
                        sqlInsertSubTypes.bindUTF8StringParameter(1, subTypesArray[i]);
                        try { sqlInsertSubTypes.execute(); }
                        catch (e if this.DBConn.lastError == 19)
                        {
                            this.log(["DiscoveredServicesSubTypes already has an entry for [",serviceID,',',subTypesArray[i],"]"].join(''));
                        }
                        sqlInsertSubTypes.reset();
                    }
                }
            }
        break;
        case "resolve":
            if (!isError)
            {
                var id = data.queryElementAt(0,Components.interfaces.nsIVariant);
                var now = new Date();
                this.log(id);
                this.ResolverInstances[id].stopTS=Math.round(now.getTime()/1000.0);
                // this.log("It took " + (this.ResolverInstances[id].stopTS - this.ResolverInstances[id].initTS) + " seconds to resolve...");
                this.ResolverInstances[id].targetHostname = data.queryElementAt(2,Components.interfaces.nsIVariant);
                this.ResolverInstances[id].targetPort = data.queryElementAt(3,Components.interfaces.nsIVariant);
                if (data.length>3)
                {
                    this.ResolverInstances[id].txtRecords = Components.classes["@mozilla.org/array;1"].createInstance(Components.interfaces.nsIMutableArray);
                    for (i=4;i<data.length;i++)
                    {
                        var trHandle = data.queryElementAt(i,Components.interfaces.nsIArray);
                        if (trHandle.length == 2)
                        {
                            var txtPair = Components.classes["@mozilla.org/array;1"].createInstance(Components.interfaces.nsIMutableArray);
                            var txtKey = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
                            txtKey.setFromVariant(trHandle.queryElementAt(0,Components.interfaces.nsIVariant));
                            var txtValue = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
                            txtValue.setFromVariant(trHandle.queryElementAt(1,Components.interfaces.nsIVariant));
                            txtPair.appendElement(txtKey,0);
                            txtPair.appendElement(txtValue,0);
                            this.ResolverInstances[id].txtRecords.appendElement(txtPair,0);
                        }
                    }
                }
            }
        break;
        case "register":
            var id = data.queryElementAt(0,Components.interfaces.nsIVariant);
            if(!isError)
            {
                flags = data.queryElementAt(1,Components.interfaces.nsIVariant);
                // this should look like for eg: "dsd_register_add"
                observerService.notifyObservers(null, "dsd_register_" + flags, id);
            } else {
                observerService.notifyObservers(null, "dsd_register_error", id);
            }
        break;                    
        default:
            this.log("handleEvent - didn't recognise " + from);
    }
  },
  // for nsISupports
  QueryInterface: function(aIID)
  {
    // add any other interfaces you support here
    if (aIID.equals(nsISupports) || aIID.equals(IDSDMANAGER))
        return this;
    return null;
  }
}

//=================================================
// Note: You probably don't want to edit anything
// below this unless you know what you're doing.
//
// Factory
var DSDMANAGERFactory = {
  singleton: null,
  createInstance: function (aOuter, aIID)
  {
    if (aOuter != null)
      throw Components.results.NS_ERROR_NO_AGGREGATION;
    if (this.singleton == null)
      this.singleton = new DSDMANAGER();
    return this.singleton.QueryInterface(aIID);
  }
};

// Module
var DSDMANAGERModule = {
  registerSelf: function(aCompMgr, aFileSpec, aLocation, aType)
  {
    aCompMgr = aCompMgr.QueryInterface(Components.interfaces.nsIComponentRegistrar);
    aCompMgr.registerFactoryLocation(CLASS_ID, CLASS_NAME, CONTRACT_ID, aFileSpec, aLocation, aType);
  },

  unregisterSelf: function(aCompMgr, aLocation, aType)
  {
    aCompMgr = aCompMgr.QueryInterface(Components.interfaces.nsIComponentRegistrar);
    aCompMgr.unregisterFactoryLocation(CLASS_ID, aLocation);        
  },
  
  getClassObject: function(aCompMgr, aCID, aIID)
  {
    if (!aIID.equals(Components.interfaces.nsIFactory))
      throw Components.results.NS_ERROR_NOT_IMPLEMENTED;

    if (aCID.equals(CLASS_ID))
      return DSDMANAGERFactory;

    throw Components.results.NS_ERROR_NO_INTERFACE;
  },

  canUnload: function(aCompMgr) { return true; }
};

//module initialization
function NSGetModule(aCompMgr, aFileSpec) { return DSDMANAGERModule; }
