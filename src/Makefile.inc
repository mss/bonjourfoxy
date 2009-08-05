CC = g++

UNAME  = $(shell uname -s 2>/dev/null | tr 'a-z' 'A-Z' || echo not)
UNAMEM = $(shell uname -m || echo not)
DISTID = $(shell lsb_release -is 2>/dev/null | tr 'a-z' 'A-Z' || echo not)

ifeq ($(UNAMEM),x86_64)
    LIB_PATH = /usr/lib64
else
    LIB_PATH = /usr/lib
endif

ifeq ($(DISTID),UBUNTU)
    XR_VERSION = $(shell xulrunner --gre-version)
    XR_LIB_PATH = $(LIB_PATH)/xulrunner-devel-$(XR_VERSION)
    XR_INC_PATH = /usr/include/xulrunner-$(XR_VERSION)
    XR_IDL_PATH = /usr/share/idl/xulrunner-$(XR_VERSION)
endif
ifeq ($(DISTID),SUSE LINUX)
    XR_VERSION = $(shell xulrunner --gre-version)
    XR_LIB_PATH = $(LIB_PATH)/xulrunner-devel-$(XR_VERSION)
    XR_INC_PATH = /usr/include/xulrunner-$(XR_VERSION)
    XR_IDL_PATH = /usr/share/idl/xulrunner-$(XR_VERSION)
endif
ifeq ($(UNAME),DARWIN)
    #XR_VERSION = 1.9.1
    #XR_RUN_PATH = $(LIB_PATH)/xulrunner-$(XR_VERSION)
    DP_XR_SDK_PATH = ../../sdk/macppc/xulrunner-sdk
    DI_XR_SDK_PATH = ../../sdk/macintel/xulrunner-sdk
    #XR_LIB_PATH = $(LIB_PATH)/xulrunner-sdk-$(XR_VERSION)
    #XR_INC_PATH = /usr/include/xulrunner-sdk-$(XR_VERSION)
    #XR_IDL_PATH = /usr/share/idl/xulrunner-sdk-$(XR_VERSION)
endif
#ifndef XR_VERSION
#    XR_VERSION = 1.9
#    XR_LIB_PATH = $(LIB_PATH)/xulrunner-sdk-$(XR_VERSION)
#    XR_INC_PATH = /usr/include/xulrunner-sdk-$(XR_VERSION)
#    XR_IDL_PATH = /usr/share/idl/xulrunner-sdk-$(XR_VERSION)
#endif


ifeq ($(UNAME),DARWIN)
    XPIDL                 = $(DI_XR_SDK_PATH)/bin/xpidl
    IDL_INCLUDES          = -I $(DI_XR_SDK_PATH)/sdk/idl -I $(DI_XR_SDK_PATH)/idl
    STABLE_IDL_INCLUDES   =
    UNSTABLE_IDL_INCLUDES =
    NSPR_INCLUDES         =
    AVAHI_INCLUDES        =
    CFLAGS                = -fshort-wchar
    LDFLAGS               = -Wl,-executable_path, -fshort-wchar
    LIBS                  = -lxpcomglue_s -lxpcom -lnspr4
else
    XPIDL                 = $(XR_RUN_PATH)/xpidl
    IDL_INCLUDES          = -I $(XR_LIB_PATH)/sdk/idl
    STABLE_IDL_INCLUDES   = -I $(XR_IDL_PATH)/stable
    UNSTABLE_IDL_INCLUDES = -I $(XR_IDL_PATH)/unstable
    ifeq ($(DISTID),SUSE LINUX)
        STABLE_IDL_INCLUDES   = -I $(XR_INC_PATH)/stable
        UNSTABLE_IDL_INCLUDES = -I $(XR_INC_PATH)/unstable
    else
        STABLE_IDL_INCLUDES   = -I $(XR_IDL_PATH)/stable
        UNSTABLE_IDL_INCLUDES = -I $(XR_IDL_PATH)/unstable
    endif
    ifeq ($(DISTID),UBUNTU)
        NSPR_INCLUDES         = -I /usr/include/nspr
    else
        NSPR_INCLUDES         = -I /usr/include/nspr4
    endif
    AVAHI_INCLUDES        = -I /usr/include/avahi-compat-libdns_sd
    CFLAGS                = -fPIC -fshort-wchar
    LDFLAGS               = -Wl,-rpath-link,$(XR_LIB_PATH)/sdk -fshort-wchar
    LIBS                  = -lxpcomglue_s -lxpcom -lnspr4 -ldns_sd
endif

ifeq ($(UNAME),DARWIN)
    IMPL_OBJS = bf$(COMP)-impl-darwin-intel.o bf$(COMP)-impl-darwin-ppc.o
else
    ifeq ($(UNAMEM),x86_64)
	IMPL_OBJS = bf$(COMP)-impl-linux64.o
    else
	IMPL_OBJS = bf$(COMP)-impl-linux.o
    endif
endif

ifeq ($(UNAME),DARWIN)
    MOD_OBJS = bf$(COMP)-module-darwin-intel.o bf$(COMP)-module-darwin-ppc.o
else
    ifeq ($(UNAMEM),x86_64)
	MOD_OBJS = bf$(COMP)-module-linux64.o
    else
	MOD_OBJS = bf$(COMP)-module-linux.o
    endif
endif

ifeq ($(UNAME),DARWIN)
    LIB_OBJS = bf$(COMP)-darwin-intel.dylib bf$(COMP)-darwin-ppc.dylib dolipo
else
    ifeq ($(UNAMEM),x86_64)
	LIB_OBJS = bf$(COMP)-linux64.so
    else
	LIB_OBJS = bf$(COMP)-linux.so
    endif
endif

all: $(ALL_OBJS)

%.h: %.idl
	$(XPIDL) $(IDL_INCLUDES) $(STABLE_IDL_INCLUDES) $(UNSTABLE_IDL_INCLUDES) -m typelib $<
	$(XPIDL) $(IDL_INCLUDES) $(STABLE_IDL_INCLUDES) $(UNSTABLE_IDL_INCLUDES) -m header $<

bf$(COMP)-impl-darwin-intel.o: bf$(COMP)-impl.cpp
	$(CC) $(CFLAGS) -w -c -o $@ -I $(DI_XR_SDK_PATH)/sdk/include -I $(DI_XR_SDK_PATH)/include/xpcom -I $(DI_XR_SDK_PATH)/idl -DXP_UNIX -DXP_MACOSX -I ../manager $<

bf$(COMP)-impl-darwin-ppc.o: bf$(COMP)-impl.cpp
	$(CC) -arch ppc $(CFLAGS) -w -c -o $@ -I $(DP_XR_SDK_PATH)/sdk/include -I $(DP_XR_SDK_PATH)/include/xpcom -I $(DP_XR_SDK_PATH)/idl -DXP_UNIX -DXP_MACOSX -I ../manager $<

bf$(COMP)-impl-%.o: bf$(COMP)-impl.cpp
	$(CC) $(CFLAGS) -w -c -o $@ -I $(XR_INC_PATH)/stable -I $(XR_INC_PATH)/unstable -DXP_UNIX -I ../manager $(NSPR_INCLUDES) $(AVAHI_INCLUDES) $<

bf$(COMP)-module-darwin-intel.o: bf$(COMP)-module.cpp
	$(CC) $(CFLAGS) -w -c -o $@ -I $(DI_XR_SDK_PATH)/sdk/include -I $(DI_XR_SDK_PATH)/include/xpcom -I $(DI_XR_SDK_PATH)/idl -DXP_UNIX -DXP_MACOSX $<

bf$(COMP)-module-darwin-ppc.o: bf$(COMP)-module.cpp
	$(CC) -arch ppc $(CFLAGS) -w -c -o $@ -I $(DP_XR_SDK_PATH)/sdk/include -I $(DP_XR_SDK_PATH)/include/xpcom -I $(DP_XR_SDK_PATH)/idl -DXP_UNIX -DXP_MACOSX $<

bf$(COMP)-module-%.o: bf$(COMP)-module.cpp
	$(CC) $(CFLAGS) -w -c -o $@ -I $(XR_INC_PATH)/stable -I $(XR_INC_PATH)/unstable -DXP_UNIX $(NSPR_INCLUDES) $(AVAHI_INCLUDES) $<

bf$(COMP)-darwin-intel.dylib: bf$(COMP)-impl-darwin-intel.o bf$(COMP)-module-darwin-intel.o
	$(CC) -L$(DI_XR_SDK_PATH)/sdk/lib -L$(DI_XR_SDK_PATH)/bin $(LDFLAGS) -dynamiclib -o $@ $^ $(LIBS)

bf$(COMP)-darwin-ppc.dylib: bf$(COMP)-impl-darwin-ppc.o bf$(COMP)-module-darwin-ppc.o
	$(CC) -arch ppc -L$(DP_XR_SDK_PATH)/sdk/lib -L$(DP_XR_SDK_PATH)/bin $(LDFLAGS) -dynamiclib -o $@ $^ $(LIBS)

bf$(COMP)-%.so: bf$(COMP)-impl-%.o bf$(COMP)-module-%.o
	$(CC) -shared -Wl,-z,defs -L$(XR_LIB_PATH)/sdk/lib -L$(XR_LIB_PATH)/bin $(LDFLAGS) -dynamiclib -o $@ $^ $(LIBS)

dolipo:
	lipo -create bf$(COMP)-darwin-{intel,ppc}.dylib -output bf$(COMP)-darwin.dylib

clean:
	rm -f $(ALL_OBJS)
