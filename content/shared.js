function checkResolver(context) {
    context.dsdmanager = Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
    var result = new context.dsdmanager.resolveService(context.serviceName,context.regType,context.regDomain,3);
    if (result.length>0)    {
        if (result.length==1)   {
            var errorArray = result.queryElementAt(0,Components.interfaces.nsIArray)
            var error = errorArray.queryElementAt(0,Components.interfaces.nsIVariant);
            var status = errorArray.queryElementAt(1,Components.interfaces.nsIVariant);
            if (error==98)  {
                window.alert("Timed out resolving '" + context.serviceName + "'");
            } else {
                window.alert("Error " + error + " State: " + status);
            }
        } else {
            var finalurl="http://";
            var targetHostname = result.queryElementAt(0,Components.interfaces.nsIVariant);
            finalurl += targetHostname;
            finalurl += ":" + result.queryElementAt(1,Components.interfaces.nsIVariant);
            var txtRecords = result.queryElementAt(2,Components.interfaces.nsIArray);
            for (var i=0;i<txtRecords.length;i++)   {
                var txtRecord = txtRecords.queryElementAt(i,Components.interfaces.nsIArray);
                if (txtRecord.queryElementAt(0,Components.interfaces.nsIVariant)=="path")  {
                    var uri = txtRecord.queryElementAt(1,Components.interfaces.nsIVariant)
                    if (uri[0]=="/")    {
                        finalurl += uri;
                    } else {
                        finalurl += "/" + uri;
                    }
                }
            }
            switch(context.target)
            {
                case "tab":
                    var win = Components.classes['@mozilla.org/appshell/window-mediator;1'].getService(Components.interfaces.nsIWindowMediator).getMostRecentWindow('navigator:browser');
                    win.openUILinkIn(finalurl, 'tab');
                break;
                case "window":
                    var win = Components.classes['@mozilla.org/appshell/window-mediator;1'].getService(Components.interfaces.nsIWindowMediator).getMostRecentWindow('navigator:browser');
                    win.openUILinkIn(finalurl, 'window');
                break;
                default:
                    window._content.location=finalurl;
            }
        }
    } else {
        context.timer = setTimeout(function(){checkResolver(context)}, 1000);
    }
}

function openLink(target,serviceName,regType,regDomain) {
    if (target=="default")  {
         var prefs = Components.classes["@mozilla.org/preferences-service;1"]
                        .getService(Components.interfaces.nsIPrefService);
         prefs = prefs.getBranch("extensions.bonjourfoxy.");
         target = prefs.getCharPref("target");
    }
    var context = new Object();
    context.target = target;
    context.count=0;
    context.serviceName = unescape(serviceName);
    context.regType = unescape(regType);
    context.regDomain = unescape(regDomain);
    context.dsdmanager = Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
    context.dsdmanager.resolveService(context.serviceName,context.regType,context.regDomain,3);
    checkResolver(context);
}