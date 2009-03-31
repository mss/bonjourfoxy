function checkResolver(context) {
    context.dsdmanager = Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
    var result = context.dsdmanager.resolveService(context.serviceName,context.regType,context.regDomain);
    var returnCode = result.queryElementAt(0,Components.interfaces.nsIVariant);
    if (returnCode==-1)
    {
        window.alert(['Unable to resolve service - (',returnCode,')'].join(''));
    }
    else if (returnCode==1)
    {
        var re = new RegExp(/(\${(srv:hostname|srv:port|txtvalue:[a-z]+|iftxtkey:[a-z]+:[a-z0-9@\-\:]+|iftxtvalue:[a-z]+:[a-z0-9@\-\:]*)})/gi);
        var returnPayload = result.queryElementAt(1,Components.interfaces.nsIArray)
        var srv = {
            hostname: returnPayload.queryElementAt(0,Components.interfaces.nsIVariant),
            port: returnPayload.queryElementAt(1,Components.interfaces.nsIVariant),
        }
        var txtRecords = {};
        var txtRecordsArray = returnPayload.queryElementAt(2,Components.interfaces.nsIArray);
        for (var i=0;i<txtRecordsArray.length;i++)   {
            var txtRecord = txtRecordsArray.queryElementAt(i,Components.interfaces.nsIArray);
            var txtKey = txtRecord.queryElementAt(0,Components.interfaces.nsIVariant);
            var txtValue = txtRecord.queryElementAt(1,Components.interfaces.nsIVariant);
            txtRecords[txtKey]=txtValue;
        }
        // var scheme = 'http://${iftxtvalue:u:${txtvalue:u}}${iftxtvalue:u:${iftxtvalue:p::${txtvalue:p}}}${iftxtvalue:u:@}${srv:hostname}:${srv:port}/${txtvalue:path}';
        var scheme = "";
        var storageService = Components.classes["@mozilla.org/storage/service;1"]
                        .getService(Components.interfaces.mozIStorageService);        
        var dbFile = Components.classes["@mozilla.org/file/directory_service;1"]
                        .getService(Components.interfaces.nsIProperties)
                        .get("ProfD", Components.interfaces.nsIFile);
        dbFile.append("bonjourfoxy.sqlite");
        var DBConn = storageService.openDatabase(dbFile);
        var sqlGetScheme = DBConn.createStatement("SELECT scheme FROM Services WHERE regtype=?1");
        sqlGetScheme.bindUTF8StringParameter(0, context.regType);
        while(sqlGetScheme.executeStep()) {
            scheme = sqlGetScheme.getUTF8String(0);
        }

        while(scheme.match(re))  {
            var m = re.exec(scheme);
            var strSearch = m[0];
            var strReplace = "";
            var endReplaceType = m[2].indexOf(':');
            var endReplaceKey = m[2].indexOf(':',endReplaceType+1);
            strReplace = (endReplaceKey==-1) ? strReplace : m[2].substring(endReplaceKey+1,m[2].length);
            endReplaceKey = (endReplaceKey==-1) ? m[2].length : endReplaceKey;
            var replaceType = m[2].split(":")[0];
            var replaceKey = m[2].split(":")[1];
            switch(replaceType)  {
                case "srv":
                    if (srv[replaceKey])    {
                        strReplace = srv[replaceKey].toString().replace('{','\\{').replace('}','\\}');
                    }
                break;
                case "txtvalue":
                    if (txtRecords[replaceKey]) {
                        strReplace = txtRecords[replaceKey].toString().replace('{','\\{').replace('}','\\}');
                    }
                break;
                case "iftxtkey":
                    if (!txtRecords.hasOwnProperty(replaceKey)) {
                        strReplace = "";
                    }
                break;            
                case "iftxtvalue":
                    if (!txtRecords[replaceKey]) {
                        strReplace = "";
                    }
                break;
            }
            scheme=scheme.replace(strSearch,strReplace);
        }
        var finalurl=scheme.replace('\\{','{').replace('\\}','}');
        dump('xp '+Components.classes['@mozilla.org/uriloader/external-protocol-service;1'].getService(Components.interfaces.nsIExternalProtocolService).isExposedProtocol(finalurl.split(':')[0])+"\n");
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
    else if (returnCode==0)
    {
        context.timer = setTimeout(function(){checkResolver(context)}, 1000);
    }
}

function openLink(target,serviceId) {
    var context = new Object();
    context.dsdmanager = Components.classes["@andrew.tj.id.au/dsdmanager;1"].getService(Components.interfaces.IDSDMANAGER);
    var serviceInfo = context.dsdmanager.IDSDMANAGER.getServiceInfoFromId(serviceId);
    if (target=="default")  {
         var prefs = Components.classes["@mozilla.org/preferences-service;1"]
                        .getService(Components.interfaces.nsIPrefService);
         prefs = prefs.getBranch("extensions.bonjourfoxy.");
         target = prefs.getCharPref("target");
    }
    context.target = target;
    context.count=0;
    context.serviceName = serviceInfo.queryElementAt(0,Components.interfaces.nsIVariant);
    context.regType = serviceInfo.queryElementAt(1,Components.interfaces.nsIVariant);
    context.regDomain = serviceInfo.queryElementAt(2,Components.interfaces.nsIVariant);
    context.dsdmanager.resolveService(context.serviceName,context.regType,context.regDomain,3);
    checkResolver(context);
}