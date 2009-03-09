function contextListEventHandler(event) {
    var node = document.popupNode;
    var pNode = node.parentNode;
    /*
    dump("context\n");
    dump(node.value + "\n");
    dump(pNode.onclick + "\n");
    dump(event.target.value + "\n");
    dump(event.bubbles + "\n");
    dump(event.type + "\n");
    dump(event.shiftKey + "\n");
    dump(event.button + "\n");
    */
    pNode.onclick(event);
}

function listEventHandler(event,target,serviceName,regType,regDomain)   {
    // dump("list\n");
    // event.shiftKey 
    // event.type == "click"
    if (event.type=="click")    {
        if (event.button=="0")  {
            if (event.shiftKey) {
                openLink("window",serviceName,regType,regDomain);
            } else {
                openLink("default",serviceName,regType,regDomain);
            }
        } else if (event.button=="1")    {
            openLink("tab",serviceName,regType,regDomain);
        }   
    } if (event.type=="command")    {
        openLink(event.target.value,serviceName,regType,regDomain);
    }
}

function updateServiceList()    {
    var obj=Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
    obj.discoverServices("_http._tcp.",null);
    var serviceList = document.getElementById('serviceList');
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
        var richlistEl = document.createElement('richlistitem');
        var descriptionEl = document.createElement('description');
        descriptionEl.setAttribute('value', serviceName);
        descriptionEl.setAttribute('crop','center');
        descriptionEl.setAttribute('flex','1');
        richlistEl.appendChild(descriptionEl);
        richlistEl.setAttribute('onclick','listEventHandler(event,"default","' + [
                escape(discoveredService.queryElementAt(2,Components.interfaces.nsIVariant)),
                escape(discoveredService.queryElementAt(1,Components.interfaces.nsIVariant)),
                escape(discoveredService.queryElementAt(0,Components.interfaces.nsIVariant))
                ].join('","') + '");');
        serviceList.appendChild(richlistEl);
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