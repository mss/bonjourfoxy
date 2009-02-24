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
}

// This is the implementation of your component.
DSDMANAGER.prototype = {
  handleEvent: function(from,data)
  {
    var valuestext = "\t";
    if (from != "resolve")  {
        for (i=0;i<data.length;i++) {
            valuestext += data.queryElementAt(i,Components.interfaces.nsIVariant) + "\t";
        }
    } else {
    if (from == "resolve")    {
        for (i=0;i<6;i++) {
            valuestext += data.queryElementAt(i,Components.interfaces.nsIVariant) + "\t";
            }
        }
        for (i=6;i<data.length;i++) {
            handle = data.queryElementAt(i,Components.interfaces.nsIArray);
            if (handle.length == 2) {
                valuestext += handle.queryElementAt(0,Components.interfaces.nsIVariant) + "=" + handle.queryElementAt(1,Components.interfaces.nsIVariant);
            }
        }
    }
    var aConsoleService = Components.classes["@mozilla.org/consoleservice;1"].
         getService(Components.interfaces.nsIConsoleService);
    aConsoleService.logStringMessage("Call from " + from + " with " + data.length + " args: " + valuestext);
  },
  get acceptEvents() { return this.acceptingEvents; },
  acceptingEvents: true,
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
