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
  Log: function(message)   {
    dump(message + "\n");
    var aConsoleService = Components.classes["@mozilla.org/consoleservice;1"].getService(Components.interfaces.nsIConsoleService);
    aConsoleService.logStringMessage(message);
  },
  BrowseInstances: Object(),
  discoverServices: function(regType,regDomain)
  {
    this.Log("discoverServices(" + regType + "," + regDomain + ")");
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
    this.Log("getDiscoveredDomains(" + domainType + ")");
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
    this.Log("getDiscoveredDomainsCount(" + domainType + ")");
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
    this.Log("getDiscoveredDomainsCount(" + domainType + ") returning: " + count);
    return count;
  },  
  getDiscoveredServices: function (regType, regDomain)
  {
    this.Log("getDiscoveredServices(" + regType + "," + regDomain + ")");
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
    this.Log("getDiscoveredServicesCount(" + regType + "," + regDomain + ")");
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
    this.Log("getDiscoveredServicesCount(" + regType + "," + regDomain + ") returning: " + count);
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
    this.Log("resolveService(" + serviceName + "," + regType + "," + regDomain + "," + timeout + ")");
    var arrayResolvedService = Components.classes["@mozilla.org/array;1"].createInstance(Components.interfaces.nsIMutableArray);
    var id = serviceName + "." + regType + "." + regDomain;
    if (!this.ResolverInstances[id])
    {
        this.Log("resolveService(" + serviceName + "," + regType + "," + regDomain + "," + timeout + "): creating resolver instance");
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
            this.Log("resolveService(" + serviceName + "," + regType + "," + regDomain + "," + timeout + ") failed: " + e);
        }
    }
    else if (this.ResolverInstances[id].obj.status == 99)
    {
        var managerError = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
        managerError.setFromVariant("99");
        arrayResolvedService.appendElement(managerError, 0);
        var lastErrorcode = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
        lastErrorcode.setFromVariant(this.ResolverInstances[id].obj.lastErrorcode);
        this.Log("resolveService(" + serviceName + "," + regType + "," + regDomain + "," + timeout + "): fatal state 99");
    }
    else if (this.ResolverInstances[id].obj.status == 2)
    {
        var targetHostname = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
        targetHostname.setFromVariant(this.ResolverInstances[id].targetHostname);
        arrayResolvedService.appendElement(targetHostname, 0);
        var targetPort = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
        targetPort.setFromVariant(this.ResolverInstances[id].targetPort);
        arrayResolvedService.appendElement(targetPort, 0);
        // var txtRecords = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
        // txtRecords.setFromVariant(this.ResolverInstances[id].txtRecords);
        arrayResolvedService.appendElement(this.ResolverInstances[id].txtRecords, 0);
        
        /*
        for (var i=0;i<this.ResolverInstances[id].txtRecords.length;i++) 
        {
            handle = this.ResolverInstances[id].txtRecords.queryElementAt(i,Components.interfaces.nsIArray);
            if (handle.length == 2)
            {
                this.Log("{key:" + handle.queryElementAt(0,Components.interfaces.nsIVariant) + ",value:" + handle.queryElementAt(1,Components.interfaces.nsIVariant) + "}");
            }
        }
        */
        
        this.Log("resolveService(" + serviceName + "," + regType + "," + regDomain + "," + timeout + "): returned data in state 2");
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

            this.Log("resolveService(" + serviceName + "," + regType + "," + regDomain + "," + timeout + "): timed out in state 1");
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
                this.Log("resolveService(" + serviceName + "," + regType + "," + regDomain + "," + timeout + "): delete timed out obj in manager state 98");
            } else {
                this.Log("resolveService(" + serviceName + "," + regType + "," + regDomain + "," + timeout + "): remaining in time out in manager state 98");
            }
        } else {
            this.Log("resolveService(" + serviceName + "," + regType + "," + regDomain + "," + timeout + "): in state 0 for unknown reason. failed to start?");
        }
    }
    this.Log("resolveService(" + serviceName + "," + regType + "," + regDomain + "," + timeout + ") returning " +  arrayResolvedService.length + " args");
    return arrayResolvedService;
  },
  RegistrationInstances: Object(),
  addService: function(serviceName, regType, targetHost, targetPort, txtKey, txtValue, regDomain)   {
    var CHARS = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'.split('');
    var chars = CHARS, uuid = [], rnd = Math.random;
    for (var i = 0; i < 15; i++) uuid[i] = chars[0 | rnd()*chars.length];
    var id = uuid.join('');
    this.RegistrationInstances[id] = Components.classes["@andrew.tj.id.au/dsdregister;1"].createInstance(Components.interfaces.IDSDREGISTER);
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
        delete this.RegistrationInstances[id];
        return ""
    }
    return id;
  },
  removeService: function(identifier)   {
    if (this.RegistrationInstances[identifier])  {
        this.RegistrationInstances[identifier].stop();
        this.RegistrationInstances[identifier]=null;
        delete this.RegistrationInstances[identifier];
    }
  },    
  handleEvent: function(from,isError,data)
  {
    var observerService = Components.classes["@mozilla.org/observer-service;1"].getService(Components.interfaces.nsIObserverService);
    this.Log("handleEvent(" + from + "," + isError + ',' + data +")");
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
                // below should look like for eg: "dsd_addregistrationdomain"
                observerService.notifyObservers(null,"dsd_" + flags + domainType + "domain",regDomain);
            }
        break;
        case "browse":
            if (!isError)   {
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
                sql.execute();
                sql.reset();
                var observerData = Components.classes["@mozilla.org/array;1"].createInstance(Components.interfaces.nsIMutableArray);
                var vServiceName = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
                vServiceName.setFromVariant(serviceName);
                observerData.appendElement(vRegDomain,0);
                var vRegDomain = Components.classes["@mozilla.org/variant;1"].createInstance(Components.interfaces.nsIWritableVariant);
                vRegDomain.setFromVariant(regDomain);
                observerData.appendElement(vRegDomain,0);
                // below should look like for eg: "dsd_add_http._tcp."
                observerService.notifyObservers(null,"dsd_" + flags + regType,observerData);
            }
        break;
        case "resolve":
            if (!isError)   {
                var id = data.queryElementAt(0,Components.interfaces.nsIVariant);
                var now = new Date();
                this.ResolverInstances[id].stopTS=Math.round(now.getTime()/1000.0);
                // this.Log("It took " + (this.ResolverInstances[id].stopTS - this.ResolverInstances[id].initTS) + " seconds to resolve...");
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
        default:
            this.Log("handleEvent - didn't recognise " + from);
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
