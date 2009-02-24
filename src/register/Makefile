GECKO_SDK := /Developer/xulrunner-1.9.0.6/sdk
XULRUNNER := /Developer/xulrunner-1.9.0.6/bin
DEFINE := -DXP_UNIX -DXP_MACOSX
all: xpt dylib
xpt:
	$(GECKO_SDK)/bin/xpidl -m header -I$(GECKO_SDK)/idl -I/Developer/xulrunner-1.9.0.6/idl -I /Users/atj/XP_Share/bonjourfoxy/src/manager dsdregister.idl 
	$(GECKO_SDK)/bin/xpidl -m typelib -I$(GECKO_SDK)/idl -I/Developer/xulrunner-1.9.0.6/idl -I /Users/atj/XP_Share/bonjourfoxy/src/manager dsdregister.idl 
impl:
	g++ -fshort-wchar -w -c -o dsdregister-impl.o -I $(GECKO_SDK)/include -I /Developer/xulrunner-1.9.0.6/include/xpcom \
	-I /Developer/xulrunner-1.9.0.6/idl $(DEFINE) dsdregister-impl.cpp -I /Users/atj/XP_Share/bonjourfoxy/src/manager
module:
	g++ -fshort-wchar -w -c -o dsdregister-module.o -I $(GECKO_SDK)/include -I /Developer/xulrunner-1.9.0.6/include/xpcom $(DEFINE) dsdregister-module.cpp
dylib: impl module
	g++ -fshort-wchar -dynamiclib -o dsdregister.dylib dsdregister-impl.o dsdregister-module.o -L$(GECKO_SDK)/lib \
	-L$(XULRUNNER) -Wl,-executable_path,$(XULRUNNER) \
	-lxpcomglue_s -lxpcom -lnspr4
clean:
	rm *.o
	rm dsdregister.h
	rm dsdregister.xpt
	rm dsdregister.dylib