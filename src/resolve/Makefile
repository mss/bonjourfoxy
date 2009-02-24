GECKO_SDK := /Developer/xulrunner-1.9.0.6/sdk
XULRUNNER := /Developer/xulrunner-1.9.0.6/bin
DEFINE := -DXP_UNIX -DXP_MACOSX
all: xpt dylib
xpt:
	$(GECKO_SDK)/bin/xpidl -m header -I$(GECKO_SDK)/idl -I/Developer/xulrunner-1.9.0.6/idl -I /Users/atj/XP_Share/bonjourfoxy/src/manager dsdresolve.idl 
	$(GECKO_SDK)/bin/xpidl -m typelib -I$(GECKO_SDK)/idl -I/Developer/xulrunner-1.9.0.6/idl -I /Users/atj/XP_Share/bonjourfoxy/src/manager dsdresolve.idl 
impl:
	g++ -fshort-wchar -w -c -o dsdresolve-impl.o -I $(GECKO_SDK)/include -I /Developer/xulrunner-1.9.0.6/include/xpcom \
	-I /Developer/xulrunner-1.9.0.6/idl $(DEFINE) dsdresolve-impl.cpp -I /Users/atj/XP_Share/bonjourfoxy/src/manager
module:
	g++ -fshort-wchar -w -c -o dsdresolve-module.o -I $(GECKO_SDK)/include -I /Developer/xulrunner-1.9.0.6/include/xpcom $(DEFINE) dsdresolve-module.cpp
dylib: impl module
	g++ -fshort-wchar -dynamiclib -o dsdresolve.dylib dsdresolve-impl.o dsdresolve-module.o -L$(GECKO_SDK)/lib \
	-L$(XULRUNNER) -Wl,-executable_path,$(XULRUNNER) \
	-lxpcomglue_s -lxpcom -lnspr4
clean:
	rm *.o
	rm dsdresolve.h
	rm dsdresolve.xpt
	rm dsdresolve.dylib
