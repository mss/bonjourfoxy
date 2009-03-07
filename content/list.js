

function updateServiceList()    {
    var obj=Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
    obj.discoverServices("_http._tcp.",null);

    var serviceList = document.getElementById('serviceList');
    if (serviceList.hasChildNodes())    {
        while (serviceList.firstChild)  {
            serviceList.removeChild(serviceList.firstChild);
        }
    }
    
    var discoveredServices = obj.getDiscoveredServices("_http._tcp.",null);
    
    for(var i=0;i<discoveredServices.length;i++)   {
        var discoveredService = discoveredServices.queryElementAt(i,Components.interfaces.nsIArray);
        var serviceName = discoveredService.queryElementAt(2,Components.interfaces.nsIVariant);


        var richlistEl = document.createElement('richlistitem');
        var descriptionEl = document.createElement('description');
        descriptionEl.setAttribute('value', serviceName);
        descriptionEl.setAttribute('crop','center');
        descriptionEl.setAttribute('flex','1');
        richlistEl.appendChild(descriptionEl);
        richlistEl.setAttribute('onclick','openLink("content","' + escape(discoveredService.queryElementAt(2,Components.interfaces.nsIVariant)) + '","' + escape(discoveredService.queryElementAt(1,Components.interfaces.nsIVariant)) + '","' + escape(discoveredService.queryElementAt(0,Components.interfaces.nsIVariant)) + '");');
        
        serviceList.appendChild(richlistEl);
        
        // listitem.setAttribute('label', foo);
        // listitem.setAttribute('onclick','openLink("content","' + escape(discoveredService.queryElementAt(2,Components.interfaces.nsIVariant)) + '","' + escape(discoveredService.queryElementAt(1,Components.interfaces.nsIVariant)) + '","' + escape(discoveredService.queryElementAt(0,Components.interfaces.nsIVariant)) + '");');
        // listitem.setAttribute('label',obj[i].replyName);
        // listitem.setAttribute('onclick','window._content.location="' + obj[i].url + '"');        
        // serviceList.appendChild(listitem);
    }
}

/*
function onTreeClicked(event){
  var tree = document.getElementById("serviceListT");
  var tbo = tree.treeBoxObject;

    try {
      // get the row, col and child element at the point
      var row = { }, col = { }, child = { };
      tbo.getCellAt(event.clientX, event.clientY, row, col, child);
    
      var cellValue = tree.view.getCellValue(row.value, col.value);
      
      window._content.location=cellValue;
    }
    catch (e) {
           return;
    }
}
*/

function dsdObserver()
{
  this.register();
}
dsdObserver.prototype = {
  observe: function(subject, topic, data) {
     var aConsoleService = Components.classes["@mozilla.org/consoleservice;1"].getService(Components.interfaces.nsIConsoleService);
     aConsoleService.logStringMessage("dsdObserver: " + topic + " " + data);
    updateServiceList();
  },
  register: function() {
    var observerService = Components.classes["@mozilla.org/observer-service;1"]
                          .getService(Components.interfaces.nsIObserverService);
    observerService.addObserver(this, "dsd_add_http._tcp.", false);
    observerService.addObserver(this, "dsd_rmv_http._tcp.", false);
  },
  unregister: function() {
    var observerService = Components.classes["@mozilla.org/observer-service;1"]
                            .getService(Components.interfaces.nsIObserverService);
    observerService.removeObserver(this, "dsd_add_http._tcp.", false);
    observerService.removeObserver(this, "dsd_rmv_http._tcp.", false);
  }
}

var dsdObserverInstance = new dsdObserver();
