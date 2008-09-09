#!/bin/bash
# There doesn't seem to be a way of specifing the output filename,
# so we'll temporarily rename the .py file and change it back later
realfilename=bonjour2content-json.py
fakefilename=bonjour2content-json-osx.py
targetfilename=bonjour2content-json-osx
targetdir=../bin
mv="$(which mv) -v"
rm="$(which rm) -fv"
make=$(which make)
python=$(which python)
freeze="/opt/local/var/macports/build/_opt_local_var_macports_sources_rsync.macports.org_release_ports_lang_python25/work/Python-2.5.2/Tools/freeze/freeze.py"
pyfile=$fakefilename
echo Renaming $realfilename temporarily....
$mv $realfilename $fakefilename
echo Freezing....
$python $freeze \
-X BaseHTTPServer \
-X Carbon \
-X Carbon.AE \
-X Carbon.Appearance \
-X Carbon.AppleEvents \
-X Carbon.CarbonEvents \
-X Carbon.ControlAccessor \
-X Carbon.Controls \
-X Carbon.Ctl \
-X Carbon.Dialogs \
-X Carbon.Dlg \
-X Carbon.Dragconst \
-X Carbon.Events \
-X Carbon.Evt \
-X Carbon.File \
-X Carbon.Files \
-X Carbon.Folder \
-X Carbon.Folders \
-X Carbon.Menu \
-X Carbon.Qd \
-X Carbon.QuickDraw \
-X Carbon.Res \
-X Carbon.TextEdit \
-X Carbon.Win \
-X Carbon.Windows \
-X EasyDialogs \
-X Finder \
-X Finder.Containers_and_folders \
-X Finder.Enumerations \
-X Finder.Files \
-X Finder.Finder_Basics \
-X Finder.Finder_items \
-X Finder.Legacy_suite \
-X Finder.Standard_Suite \
-X Finder.Type_Definitions \
-X Finder.Window_classes \
-X FixTk \
-X SocketServer \
-X StdSuites \
-X StdSuites.AppleScript_Suite \
-X StdSuites.Macintosh_Connectivity_Clas \
-X StdSuites.QuickDraw_Graphics_Suite \
-X StdSuites.QuickDraw_Graphics_Suppleme \
-X StdSuites.Required_Suite \
-X StdSuites.Standard_Suite \
-X StdSuites.Table_Suite \
-X StdSuites.Text_Suite \
-X StdSuites.Type_Names_Suite \
-X StringIO \
-X Tkconstants \
-X Tkinter \
-X __future__ \
-X __main__ \
-X _builtinSuites \
-X _builtinSuites.builtin_Suite \
-X _threading_local \
-X aepack \
-X aetools \
-X aetypes \
-X applesingle \
-X base64 \
-X bdb \
-X bisect \
-X cmd \
-X copy \
-X difflib \
-X dis \
-X distutils \
-X distutils.dep_util \
-X distutils.errors \
-X distutils.log \
-X distutils.spawn \
-X distutils.sysconfig \
-X distutils.text_file \
-X distutils.util \
-X doctest \
-X dummy_thread \
-X email \
-X email._parseaddr \
-X email.base64mime \
-X email.charset \
-X email.encoders \
-X email.errors \
-X email.feedparser \
-X email.message \
-X email.mime \
-X email.parser \
-X email.quoprimime \
-X email.utils \
-X fnmatch \
-X formatter \
-X ftplib \
-X getopt \
-X getpass \
-X gettext \
-X glob \
-X gopherlib \
-X heapq \
-X htmlentitydefs \
-X htmllib \
-X httplib \
-X ic \
-X inspect \
-X linecache \
-X locale \
-X macfs \
-X macostools \
-X macpath \
-X macresource \
-X macurl2path \
-X markupbase \
-X mimetools \
-X mimetypes \
-X new \
-X ntpath \
-X nturl2path \
-X opcode \
-X optparse \
-X os2emxpath \
-X pdb \
-X pickle \
-X pkgutil \
-X popen2 \
-X pprint \
-X py_compile \
-X pydoc \
-X quopri \
-X random \
-X repr \
-X rfc822 \
-X sgmllib \
-X shlex \
-X string \
-X subprocess \
-X tempfile \
-X textwrap \
-X threading \
-X token \
-X tokenize \
-X traceback \
-X tty \
-X unittest \
-X urllib \
-X urlparse \
-X uu \
-X warnings \
-X webbrowser \
$pyfile \
-m encodings.utf_8
echo Building....
$make
echo Moving $realfilename back....
$mv $fakefilename $realfilename
echo Cleaning up....
$rm *.c *.o Makefile
echo Moving output to final destination
$mv $targetfilename $targetdir