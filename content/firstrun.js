window.addEventListener("load", FirstRunCheck, false);
 
function FirstRunCheck()
{
    var prefs = Components.classes["@mozilla.org/preferences-service;1"]
                .getService(Components.interfaces.nsIPrefService);
    prefs = prefs.getBranch("extensions.bonjourfoxy.");
    var curRev=prefs.getIntPref("rev", false);
    var newRev=1;
    var now=new Date();
    if(curRev!=newRev)   {
        prefs.setIntPref("rev",newRev);
        if (curRev==0)  {
            databaseInit();
            prefs.setIntPref("hts", Math.round(now.getTime()/1000.0));
            setTimeout("AddToolbarItem();", 0);
            setTimeout('toggleSidebar("viewBonjourServices");',2);
        }
        setTimeout("OpenWelcome();", 1);
    }
}

function databaseInit()   {
  var storageService = Components.classes["@mozilla.org/storage/service;1"]
                        .getService(Components.interfaces.mozIStorageService);

  var dbFile = Components.classes["@mozilla.org/file/directory_service;1"]
                    .getService(Components.interfaces.nsIProperties)
                    .get("ProfD", Components.interfaces.nsIFile);
  dbFile.append("bonjourfoxy.sqlite");
  var DBConn = storageService.openDatabase(dbFile);
  var dbQueries = ['                                    \
CREATE TABLE Services (                                 \
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,    \
    "regtype" TEXT,                                     \
    "scheme" TEXT,                                      \
    "label" TEXT,                                       \
    UNIQUE("regtype")                                   \
);                                                      \
    ','                                                 \
CREATE TABLE ServiceSubtypes (                          \
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,    \
    "s_id" INTEGER NOT NULL,                            \
    "subtype" TEXT,                                     \
    "label" TEXT,                                       \
    UNIQUE("id", "s_id", "subtype", "label")            \
);                                                      \
    ','                                                 \
CREATE TABLE ServicesLastInsert (                       \
    "row_id" INTEGER                                    \
);                                                      \
    ','                                                 \
INSERT INTO ServicesLastInsert values (-1);             \
    ','                                                 \
CREATE TRIGGER SST_s_id_ENFORCE                         \
BEFORE INSERT ON ServiceSubtypes                        \
FOR EACH ROW BEGIN                                      \
    SELECT RAISE(ROLLBACK, "ServiceSubtypes(s_id) must match one of Services(id)")  \
    WHERE (SELECT id FROM Services WHERE id = NEW.s_id) IS NULL;    \
END;                                                    \
    ','                                                 \
CREATE TRIGGER S_SST_CLEAN                              \
BEFORE DELETE ON Services                               \
FOR EACH ROW BEGIN                                      \
    DELETE from ServiceSubtypes WHERE s_id = OLD.id;    \
END;                                                    \
    ','                                                 \
INSERT INTO Services (regtype, scheme, label)           \
VALUES (                                                \
    "_http._tcp.",                                      \
    "http://${iftxtvalue:u:${txtvalue:u}}${iftxtvalue:u:${iftxtvalue:p::${txtvalue:p}}}${iftxtvalue:u:@}${srv:hostname}:${srv:port}/${txtvalue:path}",  \
    "Websites"                                          \
    );                                                  \
    ','                                                 \
INSERT INTO ServiceSubtypes (s_id, subtype, label)      \
VALUES (1, "_wiki", "Wikis");                           \
    ','                                                 \
INSERT INTO ServiceSubtypes (s_id, subtype, label)      \
VALUES (1, "_printer", "Printers");                     \
    ','                                                 \
INSERT INTO Services (regtype, scheme, label)           \
VALUES ("_ssh._tcp.", "ssh://${srv:hostname}:${srv:port}/","SSH");  \
    '];
    for (i=0;i<dbQueries.length;i++)    {
        try { DBConn.executeSimpleSQL(dbQueries[i]); }
        catch (e)   {
            dump (['Error executing dbQueries['+i+']',DBConn.lastError,DBConn.lastErrorString,"\n"].join(' '));
            break;
        }
    }
    
}

function AddToolbarItem()
{
    try {
        var firefoxnav = window.parent.document.getElementById("nav-bar");
        var curSet = firefoxnav.currentSet;
        if (curSet.indexOf("bonjourfoxy-toolbar-button") == -1)
        {
            var set;
            if (curSet.indexOf("home-button") != -1)
            {
                set = curSet.replace(/home-button/, "home-button,bonjourfoxy-toolbar-button");
            }
            else
            {
                set = curSet + ",bonjourfoxy-toolbar-button";
            }
            firefoxnav.setAttribute("currentset", set);
            firefoxnav.currentSet = set;
            document.persist("nav-bar", "currentset");
            // If you don't do the following call, funny things happen
            try {
                BrowserToolboxCustomizeDone(true);
            }
            catch (e) {}
        }
    }
    catch(e) { }
}

function OpenWelcome()
{
    var win = Components.classes['@mozilla.org/appshell/window-mediator;1'].getService(Components.interfaces.nsIWindowMediator).getMostRecentWindow('navigator:browser');
    win.openUILinkIn('chrome://bonjourfoxy/content/firstrun.html', 'tab');
}