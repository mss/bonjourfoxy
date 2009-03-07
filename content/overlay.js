var bonjourfoxy = {
  onLoad: function() {
    // initialization code
    this.initialized = true;
    this.strings = document.getElementById("bonjourfoxy-strings");
  },
  onMenuItemCommand: function(e) {
    toggleSidebar("viewBonjourServices");
  },
  onToolbarButtonCommand: function(e) {
    // just reuse the function above
    bonjourfoxy.onMenuItemCommand(e);
  }
};

function menuAddServices() {
    var menu = document.getElementById("bonjourMenuPopup");
    while (menu.childNodes.length>3)   {
        menu.removeChild(menu.childNodes[menu.childNodes.length-1]);
    }

    var obj=Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
    obj.discoverServices("_http._tcp.",null);

    var discoveredServices = obj.getDiscoveredServices("_http._tcp.",null);

    if (discoveredServices.length==0)   {
        var item = document.createElement("menuitem");
        item.setAttribute("label","No services found");
        item.setAttribute("disabled",true);
        menu.appendChild(item);
    } else {            
        for(var i=0;i<discoveredServices.length;i++)   {
            var discoveredService = discoveredServices.queryElementAt(i,Components.interfaces.nsIArray);
            var foo = discoveredService.queryElementAt(2,Components.interfaces.nsIVariant);
            var item = document.createElement('menuitem');
            item.setAttribute('label', foo);
            item.setAttribute('oncommand','openLink("content","' + escape(discoveredService.queryElementAt(2,Components.interfaces.nsIVariant)) + '","' + escape(discoveredService.queryElementAt(1,Components.interfaces.nsIVariant)) + '","' + escape(discoveredService.queryElementAt(0,Components.interfaces.nsIVariant)) + '");');
            // listitem.setAttribute('onclick','openLink("content","' + escape(discoveredService.queryElementAt(2,Components.interfaces.nsIVariant)) + '","' + escape(discoveredService.queryElementAt(1,Components.interfaces.nsIVariant)) + '","' + escape(discoveredService.queryElementAt(0,Components.interfaces.nsIVariant)) + '");');
            // listitem.setAttribute('label',obj[i].replyName);
            // listitem.setAttribute('onclick','window._content.location="' + obj[i].url + '"');        
            menu.appendChild(item);
        }
    }
}

window.addEventListener("load", function(e) { bonjourfoxy.onLoad(e); }, false);
