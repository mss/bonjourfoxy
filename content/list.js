function listEventHandler(event)    {
    if (event.type=='click' && event.button == 2)   { return; } // context menu click
    var linkTarget="default";
    var serviceId = event.explicitOriginalTarget.value;
    if (event.type=='command')  {
        dump([event.type,event.target.value,document.popupNode.parentNode.value,''].join("\n"));
        serviceId=document.popupNode.parentNode.value;
        linkTarget=event.target.value;
    } else {
        if (event.shiftKey) {
            linkTarget="window";
        }
        if (event.button=="1") {
            linkTarget="tab";
        }
    }
    openLink(linkTarget,serviceId);
}

function updateServiceList()    {
    var serviceList = document.getElementById('serviceList');
    serviceList.setAttribute('onclick','listEventHandler(event)');
    if (serviceList.hasChildNodes())
    {
        while (serviceList.firstChild)  {
            serviceList.removeChild(serviceList.firstChild);
        }
    }
    var dsdManager=Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
    var storageService = Components.classes["@mozilla.org/storage/service;1"]
                    .getService(Components.interfaces.mozIStorageService);        
    var dbFile = Components.classes["@mozilla.org/file/directory_service;1"]
                    .getService(Components.interfaces.nsIProperties)
                    .get("ProfD", Components.interfaces.nsIFile);
    dbFile.append("bonjourfoxy.sqlite");
    var DBConn = storageService.openDatabase(dbFile);
    var sqlGetRegTypes = DBConn.createStatement("SELECT regtype, label FROM Services");
    while(sqlGetRegTypes.executeStep()) {
        var regType = sqlGetRegTypes.getUTF8String(0);
        var label = sqlGetRegTypes.getUTF8String(1);
        var discoveredServices = dsdManager.getDiscoveredServices(regType,null);
        for(var i=0;i<discoveredServices.length;i++)
        {
            var discoveredService = discoveredServices.queryElementAt(i,Components.interfaces.nsIArray);
            var serviceName = discoveredService.queryElementAt(2,Components.interfaces.nsIVariant);
            var listItem = document.createElement('listitem');
            listItem.setAttribute('label', [serviceName,' (',label,')'].join(''));
            listItem.setAttribute('value', discoveredService.queryElementAt(3,Components.interfaces.nsIVariant));
            serviceList.appendChild(listItem);
        }
    }
}

function dsdObserver()
{
  this.register();
}
dsdObserver.prototype = {
  handlers: {},
  removeHandlerObservers: function()  {
        for (property in this.handlers) {
            this.observerService.removeObserver(this, "dsd_service_add:" + property, false);
            this.observerService.removeObserver(this, "dsd_service_rmv:" + property, false);
        }
  },
  addHandlerObservers: function() {
        for (property in this.handlers) {
            this.observerService.addObserver(this, "dsd_service_add:" + property, false);
            this.observerService.addObserver(this, "dsd_service_rmv:" + property, false);
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
        var sqlGetRegTypes = DBConn.createStatement("SELECT regtype, label FROM Services");
        var newHandlers = {};
        while(sqlGetRegTypes.executeStep()) {
            var regType = sqlGetRegTypes.getUTF8String(0);
            var label = sqlGetRegTypes.getUTF8String(0);
            newHandlers[regType] = label;
        }
        this.handlers = newHandlers;
        this.addHandlerObservers();
  },
  observe: function(subject, topic, data) {
    if (topic=="nsPref:changed")    {
        if (data=="hts")    {
            this.setHandlers();
        }
    }
    if (topic.match(/^dsd_service_/)) {
        updateServiceList();   
    }
  },
  register: function() {
    this.prefs = Components.classes["@mozilla.org/preferences-service;1"]
        .getService(Components.interfaces.nsIPrefService)
        .getBranch("extensions.bonjourfoxy.");
    this.prefs.QueryInterface(Components.interfaces.nsIPrefBranch2);
    this.prefs.addObserver("", this, false);
    this.observerService = Components.classes["@mozilla.org/observer-service;1"]
                          .getService(Components.interfaces.nsIObserverService);
    this.setHandlers();
  },
  unregister: function() {
    this.removeHandlerObservers();
    this.observerService = Components.classes["@mozilla.org/observer-service;1"]
                            .getService(Components.interfaces.nsIObserverService);
  }
}

var dsdObserverInstance = new dsdObserver();