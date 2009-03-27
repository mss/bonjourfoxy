GECKO_SDK := /Developer/xulrunner-1.9.0.6/sdk
XULRUNNER := /Developer/xulrunner-1.9.0.6/bin
DEFINE := -DXP_UNIX -DXP_MACOSX
all: xpt
xpt:
	$(GECKO_SDK)/bin/xpidl -m header -I$(GECKO_SDK)/idl -I/Developer/xulrunner-1.9.0.6/idl bfnotifier.idl 
	$(GECKO_SDK)/bin/xpidl -m typelib -I$(GECKO_SDK)/idl -I/Developer/xulrunner-1.9.0.6/idl bfnotifier.idl 
clean:
	rm bfnotifier.h
	rm bfnotifier.xpt