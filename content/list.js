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
    /*
    var obj=Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
    var serviceInfo = obj.IDSDMANAGER.getServiceInfoFromId(serviceId);
    var serviceName = serviceInfo.queryElementAt(0,Components.interfaces.nsIVariant);
    var regType = serviceInfo.queryElementAt(1,Components.interfaces.nsIVariant);
    var regDomain = serviceInfo.queryElementAt(2,Components.interfaces.nsIVariant);
    */
    openLink(linkTarget,serviceId);// serviceName,regType,regDomain);
}

function updateServiceList()    {
    var obj=Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
    obj.discoverServices("_http._tcp.",null);
    var serviceList = document.getElementById('serviceList');
    serviceList.setAttribute('onclick','listEventHandler(event)');
    if (serviceList.hasChildNodes())
    {
        while (serviceList.firstChild)  {
            serviceList.removeChild(serviceList.firstChild);
        }
    }
    var discoveredServices = obj.getDiscoveredServices("_http._tcp.",null);
    for(var i=0;i<discoveredServices.length;i++)
    {
        var discoveredService = discoveredServices.queryElementAt(i,Components.interfaces.nsIArray);
        var serviceName = discoveredService.queryElementAt(2,Components.interfaces.nsIVariant);
        var listItem = document.createElement('listitem');
        listItem.setAttribute('label', serviceName);
        listItem.setAttribute('value', discoveredService.queryElementAt(3,Components.interfaces.nsIVariant));
        serviceList.appendChild(listItem);
    }
}

function dsdObserver()
{
  this.register();
}
dsdObserver.prototype = {
  observe: function(subject, topic, data) {
    updateServiceList();
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

var dsdObserverInstance = new dsdObserver();