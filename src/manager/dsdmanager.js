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
  this.DBConn = this.storageService.openDatabase(null);
  this.DBConn.executeSimpleSQL('CREATE TABLE DiscoveredServices ( "regdomain" text, "regtype" text, "servicename" text, "ifindex" integer, UNIQUE ("regdomain", "regtype", "servicename", "ifindex"))');
  this.DBConn.executeSimpleSQL('CREATE TABLE DiscoveredDomains ("regdomain" text, "domaintype" text, "ifindex" integer, UNIQUE("regdomain", "domaintype", "ifindex"))');
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
    var expression = "^(_[a-zA-Z0-9\-]{1,14}\.)+_(ud|tc)p\.(\,[a-zA-Z0-9\-]{1,14})*$";
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
    if (domainType == null) {
        var sqlDiscoveredDomains = this.DBConn.createStatement("SELECT * FROM DiscoveredDomains GROUP BY regdomain, domaintype");
    } else {
        var sqlDiscoveredDomains = this.DBConn.createStatement("SELECT * FROM DiscoveredDomains WHERE domaintype=?1 GROUP BY regdomain, domaintype");        
        sqlDiscoveredDomains.bindUTF8StringParameter(0, domainType);
    }
    while(sqlDiscoveredDomains.executeStep())   {
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
    if (domainType == null) {
        sqlCountDiscoveredDomains = this.DBConn.createStatement("SELECT COUNT(1) FROM DiscoveredDomains GROUP BY regdomain, domaintype");
    } else {
        sqlCountDiscoveredDomains = this.DBConn.createStatement("SELECT COUNT(1) FROM DiscoveredDomains WHERE domaintype=?1 GROUP BY regdomain, domaintype");
        sqlCountDiscoveredDomains.bindUTF8StringParameter(0, domainType);
    }
    /* there's gotta be a better way... */
    while (sqlCountDiscoveredDomains.executeStep()) {
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
    var sqlDiscoveredServices = null;
    if (regDomain==null)    {
        sqlDiscoveredServices = this.DBConn.createStatement("SELECT regdomain, regtype, servicename FROM DiscoveredServices WHERE regtype = ?1 GROUP BY regdomain, regtype, servicename");
    } else {
        sqlDiscoveredServices = this.DBConn.createStatement("SELECT regdomain, regtype, servicename FROM DiscoveredServices WHERE regtype = ?1 AND regdomain = ?2 GROUP BY regdomain, regtype, servicename");
        sqlDiscoveredServices.bindUTF8StringParameter(1, regDomain);
    }
    sqlDiscoveredServices.bindUTF8StringParameter(0, regType);
    while (sqlDiscoveredServices.executeStep()) {
      var arrayDiscoveredService = Components.classes["@mozilla.org/array;1"].createInstance(Components.interfaces.nsIMutableArray);
      // discoveredService.regDomain = sqlDiscoveredServices.getUTF8String(0);
      var regDomain = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
      regDomain.setFromVariant(sqlDiscoveredServices.getUTF8String(0));
      arrayDiscoveredService.appendElement(regDomain, 0);
      // discoveredService.regType = sqlDiscoveredServices.getUTF8String(1);
      var regType = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
      regType.setFromVariant(sqlDiscoveredServices.getUTF8String(1));
      arrayDiscoveredService.appendElement(regType, 0);
      // discoveredService.serviceName = sqlDiscoveredServices.getUTF8String(2)
      var serviceName = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
      serviceName.setFromVariant(sqlDiscoveredServices.getUTF8String(2));
      arrayDiscoveredService.appendElement(serviceName, 0);
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
  ResolverInstance: function()  {
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
  resolveService: function(serviceName,regType,regDomain,timeout)
  {
    var invocationTxt = "resolveServices(" + Array.prototype.slice.call(arguments).join(",") + ")";
    this.log(invocationTxt);
    var arrayResolvedService = Components.classes["@mozilla.org/array;1"].createInstance(Components.interfaces.nsIMutableArray);
    var id = serviceName + "." + regType + regDomain;
    if (!this.ResolverInstances[id])
    {
        this.log(invocationTxt + ": creating resolver instance");
        this.ResolverInstances[id] = new this.ResolverInstance();
        this.ResolverInstances[id].obj.name = serviceName;
        this.ResolverInstances[id].obj.registrationType = regType;
        this.ResolverInstances[id].obj.registrationDomain = regDomain;
        if (timeout<6 && timeout>0) this.ResolverInstances[id].timeout = timeout;
        try
        {
            this.ResolverInstances[id].obj.start();
        }
        catch (e)
        {
            this.log([invocationTxt," failed: ",e].join(""));
        }
    }
    else if (this.ResolverInstances[id].obj.status == 99)
    {
        var managerError = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
        managerError.setFromVariant("99");
        arrayResolvedService.appendElement(managerError, 0);
        var lastErrorcode = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
        lastErrorcode.setFromVariant(this.ResolverInstances[id].obj.lastErrorcode);
        this.log(invocationTxt + ": fatal state 99");
    }
    else if (this.ResolverInstances[id].obj.status == 2)
    {
        var targetHostname = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
        targetHostname.setFromVariant(this.ResolverInstances[id].targetHostname);
        arrayResolvedService.appendElement(targetHostname, 0);
        var targetPort = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
        targetPort.setFromVariant(this.ResolverInstances[id].targetPort);
        arrayResolvedService.appendElement(targetPort, 0);
        arrayResolvedService.appendElement(this.ResolverInstances[id].txtRecords, 0);
        this.log(invocationTxt + ": returned data in state 2");
    }
    else if (this.ResolverInstances[id].obj.status == 1)
    {
        var now = new Date();
        var waitTime=Math.round(now.getTime()/1000.0)-this.ResolverInstances[id].initTS;
        if (waitTime>this.ResolverInstances[id].timeout)
        {
            var errorArray = Components.classes["@mozilla.org/array;1"].createInstance(Components.interfaces.nsIMutableArray);
            var managerError = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
            managerError.setFromVariant("98");
            errorArray.appendElement(managerError, 0);
            var lastErrorcode = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
            lastErrorcode.setFromVariant(this.ResolverInstances[id].obj.lastErrorcode);
            errorArray.appendElement(lastErrorcode, 0);
            
            arrayResolvedService.appendElement(errorArray, 0);
            
            this.ResolverInstances[id].obj.stop();
            this.ResolverInstances[id].stopTS=Math.round(now.getTime()/1000.0);

            this.log(invocationTxt + ": timed out in state 1");
        }
    }
    else if (this.ResolverInstances[id].obj.status == 0)
    {
        if ( (this.ResolverInstances[id].stopTS-this.ResolverInstances[id].initTS)>this.ResolverInstances[id].timeout )
        {
            var managerError = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
            managerError.setFromVariant("98");
            arrayResolvedService.appendElement(managerError, 0);
            var lastErrorcode = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
            lastErrorcode.setFromVariant(this.ResolverInstances[id].obj.lastErrorcode);
            var now = new Date();
            if ((Math.round(now.getTime()/1000.0) - this.ResolverInstances[id].stopTS)>5)   {
                this.ResolverInstances[id]=null;
                delete this.ResolverInstances[id];
                this.log(invocationTxt + ": delete timed out obj in manager state 98");
            } else {
                this.log(invocationTxt + ": remaining in time out in manager state 98");
            }
        } else {
            this.log(invocationTxt + ": in state 0 for unknown reason. failed to start?");
        }
    }
    this.log([invocationTxt,"returning",arrayResolvedService.length,"args"].join(" "));
    return arrayResolvedService;
  },
  RegistrationInstances: Object(),
  addService: function(serviceName, regType, targetHost, targetPort, txtKey, txtValue, regDomain)   {
    var invocationTxt = "addService(" + Array.prototype.slice.call(arguments).join(",") + ")";
    this.log(invocationTxt);
    if (!this.validServiceName(serviceName) || !this.validRegistrationType(regType)) {
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
    try {
        this.RegistrationInstances[id].start();
    }
    catch (e)   {
        this.RegistrationInstances[id]=null;
        return;
    }
    this.log([invocationTxt,"returning:",id].join(" "));
    return id;
  },
  removeService: function(identifier)   {
    var invocationTxt = "removeService(" + Array.prototype.slice.call(arguments).join(",") + ")";
    this.log(invocationTxt);
    if (this.RegistrationInstances[identifier])  {
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
    switch(from)    {
        case "enumerate":
            if (!isError)   {
                flags = data.queryElementAt(0,Components.interfaces.nsIVariant);
                if (flags == 'add')
                {
                    var sql = this.DBConn.createStatement("INSERT INTO DiscoveredDomains VALUES (?1, ?2, ?3)");
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
                // below should look like for eg: "dsd_domain_add_registration"
                observerService.notifyObservers(null, ["dsd","domain",flags,domainType].join("_"), regDomain);
            }
        break;
        case "browse":
            if (!isError)   {
                var notify = true;
                flags = data.queryElementAt(0,Components.interfaces.nsIVariant);
                if (flags == "add")
                {
                    var sql = this.DBConn.createStatement("INSERT INTO DiscoveredServices VALUES (?1, ?2, ?3, ?4)");
                } else {
                    var sql = this.DBConn.createStatement("DELETE FROM DiscoveredServices WHERE regdomain = ?1 AND regtype = ?2 AND servicename = ?3 AND ifindex = ?4");
                }
                var regDomain = data.queryElementAt(4,Components.interfaces.nsIVariant);
                sql.bindUTF8StringParameter(0, regDomain);
                var regType = data.queryElementAt(3,Components.interfaces.nsIVariant);
                sql.bindUTF8StringParameter(1, regType);
                var serviceName = data.queryElementAt(2,Components.interfaces.nsIVariant);
                sql.bindUTF8StringParameter(2, serviceName);
                var interfaceIndex = data.queryElementAt(1,Components.interfaces.nsIVariant);
                sql.bindInt32Parameter(3, interfaceIndex);
                dump(["browse :",regDomain,":",regType,":",serviceName,":",interfaceIndex].join(" ") + "\n");
                try {
                    sql.execute();
                }
                catch (e if this.DBConn.lastError == 19)
                {
                    notify = false;
                    this.log("DiscoveredServices already contains a record for ['" + [regDomain,regType,serviceName,interfaceIndex].join("','") + "']");
                }
                sql.reset();
                if (notify) {
                    observerService.notifyObservers(null, ["dsd","service",flags,regType].join("_"), serviceName);
                }
            }
        break;
        case "resolve":
            if (!isError)   {
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
            if(!isError)    {
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
