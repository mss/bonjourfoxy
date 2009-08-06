BonjourFoxy
===========

This repo should contain everything needed to build a BonjourFoxy release from scratch. If you 
redistribute BonjourFoxy please change all the identifiers in the to be unique. That includes but is 
no limited to the names and UUID's used by the binary components. If you do not want to rebuild the 
binary components then specify BonjourFoxy as a dependency in your extension (see 
developer.mozilla.org for how to do this). 

Building Binary Components
--------------------------

I store the xulrunner sdk's for each platform in ./sdk/archive. I populate this folder using the 
'get-xr.sh' shell script which will need to be updated to use your local moz mirror and output to 
the appropriate path prior to use. To switch to a particular xulrunner release I use the 
'switch-xr.sh' shell script which again will need to be updated with appropriate paths before being 
used. When it's run, it extracts the SDK's for each platform to ./sdk/${platform} where ${platform} 
is linux, macintel, macppc and win32. I share the project directory to Windows and Ubuntu from OS X 
via VMware Fusion's Shared Folders so no further replication is necessary. Both the 'switch-xr.sh' 
and 'get-xr.sh' shell scripts require one parameter - a xulrunner release.

Building on OS X / Linux
~~~~~~~~~~~~~~~~~~~~~~~~

On OS X if you've installed the Developer Tools you are right to go. On Linux you'll need to install 
your distributions xulrunner development package and Avahi-Bonjour development packages. At present 
even though the shell scripts grab and extract xulrunner releases for Linux they're unused. Once 
you've got the prerequistes sorted, just change to the src directory and run make.

Building on Windows
~~~~~~~~~~~~~~~~~~~

I install Visual C++ 2008 Express Edition and the Bonjour Development libraries to their default 
locations and then map a drive letter to the Shared Folder. There's a batch file called 'make.bat' 
in the source folder which will build the components. It accepts the parameter 'clean' to run a 
clean on each component prior to building.

Assembling the Extension
------------------------

The 'gen-ext.sh' shell script creates the final structure of the extension in the directory 
scratch/<first-argument>. Once this is done you can test the extension by going to a Firefox Profile 
folder's extension directory and creating a text filed name 'bonjourfoxy@andrew.tj.id.au' that 
contains the full-path to scratch/<first-argument>. If BonjourFoxy isn't picked up by Firefox after 
a restart, it may be necessary to touch .autoreg in your Profile folder or remove 'compreg.dat' 
and/or 'xpti.dat' from your Profile folder to get Firefox to detect it. Before doing a release make 
sure you've updated scratch/<first-argument>/install.rdf appropriately. To redistrbute the extension
just create a zip file with an extension of XPI containing the contents of scratch/<first-argument>.
