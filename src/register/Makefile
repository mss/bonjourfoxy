UNAME_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')
PATH_F := $(shell pwd )
PATH_B := $(shell basename $(PATH_F) )
TARGET := $(PATH_B)-$(UNAME_S)
IDL_DEF := dsd$(PATH_B).idl
IMPL_S := dsd$(PATH_B)-impl.cpp
IMPL_O := dsd$(TARGET)-impl.o
MODU_S := dsd$(PATH_B)-module.cpp
MODU_O := dsd$(TARGET)-module.o
ifeq ($(UNAME_S),Darwin)
	XR_PATH := /Developer/xulrunner-1.9.0.6
	DEFINE := -DXP_UNIX -DXP_MACOSX
	DSDM_PATH := ~atj/XP_Share/bonjourfoxy/src/manager
	DYLIB_F := -Wl,-executable_path,$(XR_BIN)
	DYLIB_O := dsd$(TARGET).dylib
endif
ifeq ($(UNAME_S),Linux)
	XR_PATH := /home/atj/Source/xulrunner-sdk
	DEFINE := -DXP_UNIX
	DSDM_PATH := /home/atj/src/manager
	DYLIB_F := -Wl,-rpath-link,$(XR_SDK)
	DYLIB_O := dsd$(TARGET).o
	G_EXTRAF := -shared -Wl,-z,defs
	G_EXTRAL := -ldns_sd
endif
XR_SDK := $(XR_PATH)/sdk
XR_BIN := $(XR_PATH)/bin
XR_IDL := $(XR_PATH)/idl
all: xpt dylib
xpt:
	$(XR_SDK)/bin/xpidl -m header -I$(XR_SDK)/idl -I$(XR_IDL) -I $(DSDM_PATH) $(IDL_DEF)
	$(XR_SDK)/bin/xpidl -m typelib -I$(XR_SDK)/idl -I$(XR_IDL) -I $(DSDM_PATH) $(IDL_DEF)
impl:
	g++ -fshort-wchar -w -c -o $(IMPL_O) -I $(XR_SDK)/include -I $(XR_PATH)/include/xpcom \
	-I /Developer/xulrunner-1.9.0.6/idl $(DEFINE) -I $(DSDM_PATH) $(IMPL_S)
module:
	g++ -fshort-wchar -w -c -o $(MODU_O) -I $(XR_SDK)/include -I $(XR_PATH)/include/xpcom $(DEFINE) $(MODU_S)
dylib: impl module
	g++  $(G_EXTRAF) -L$(XR_SDK)/lib -L$(XR_BIN) $(DYLIB_F) -fshort-wchar -dynamiclib -o $(DYLIB_O) $(IMPL_O) $(MODU_O) \
	  -lxpcomglue_s -lxpcom -lnspr4 $(G_EXTRAL)
# -include xpcom-config.h after target
clean:
	rm *.o
	rm dsd$(PATH_B).h
	rm dsd$(PATH_B).xpt
	rm dsd$(TARGET).dylib