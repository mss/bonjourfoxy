#!/bin/bash

CC=g++

UNAME=`uname -s 2>/dev/null | tr 'a-z' 'A-Z' || echo not`

UL_XR_SDK_PATH=/home/atj/Source/xulrunner-sdk
DP_XR_SDK_PATH=/Developer/xulrunner-1.9.0.6-ppc
DI_XR_SDK_PATH=/Developer/xulrunner-1.9.0.6-intel

BASE_DIR=`dirname $0`
TARGETS=`cd ${BASE_DIR}; for i in * ; do if [ -d $i ]; then echo $i ; fi ; done`

buildxpt()  {

    if [ ${UNAME} == "DARWIN" ]; then
        XR_PATH=${DI_XR_SDK_PATH}
        DSDM_PATH=/Users/atj/Projects/bonjourfoxy/src/manager
    else
        XR_PATH=${UL_XR_SDK_PATH}
    	DSDM_PATH=/home/atj/bonjourfoxy/src/manager
    fi
    XR_SDK=${XR_PATH}/sdk
    XR_BIN=${XR_PATH}/bin
    XR_IDL=${XR_PATH}/idl

    echo ${XR_SDK}/bin/xpidl -m header -I${XR_SDK}/idl -I ${XR_IDL} -I ${DSDM_PATH} *.idl

}

buildimpl() {
    if [ ${UNAME} == "DARWIN" ]; then
        DSDM_PATH=/Users/atj/Projects/bonjourfoxy/src/manager

        XR_PATH=${DI_XR_SDK_PATH}
        XR_SDK=${XR_PATH}/sdk
        XR_BIN=${XR_PATH}/bin
        XR_IDL=${XR_PATH}/idl
        ${CC} -fshort-wchar -w -c -o dsd${T}-impl-darwin-intel.o -I ${XR_SDK}/include -I ${XR_PATH}/include/xpcom -I ${XR_IDL} -DXP_UNIX -DXP_MACOSX -I ${DSDM_PATH} dsd${T}-impl.cpp

        XR_PATH=${DP_XR_SDK_PATH}
        XR_SDK=${XR_PATH}/sdk
        XR_BIN=${XR_PATH}/bin
        XR_IDL=${XR_PATH}/idl
        ${CC} -arch ppc -fshort-wchar -w -c -o dsd${T}-impl-darwin-ppc.o -I ${XR_SDK}/include -I ${XR_PATH}/include/xpcom -I ${XR_IDL} -DXP_UNIX -DXP_MACOSX -I ${DSDM_PATH} dsd${T}-impl.cpp

    else
	DSDM_PATH=/home/atj/bonjourfoxy/src/manager

        XR_PATH=${UL_XR_SDK_PATH}
        XR_SDK=${XR_PATH}/sdk
        XR_BIN=${XR_PATH}/bin
        XR_IDL=${XR_PATH}/idl

        ${CC} -fshort-wchar -w -c -o dsd${T}-impl-linux.o -I ${XR_SDK}/include -I ${XR_PATH}/include/xpcom -I ${XR_IDL} -DXP_UNIX -I ${DSDM_PATH} dsd${T}-impl.cpp            
    fi
}

buildmodule() {
    if [ ${UNAME} == "DARWIN" ]; then
        DSDM_PATH=/Users/atj/Projects/bonjourfoxy/src/manager

        XR_PATH=${DI_XR_SDK_PATH}
        XR_SDK=${XR_PATH}/sdk
        XR_BIN=${XR_PATH}/bin
        XR_IDL=${XR_PATH}/idl
        ${CC} -fshort-wchar -w -c -o dsd${T}-module-darwin-intel.o -I ${XR_SDK}/include -I ${XR_PATH}/include/xpcom -I ${XR_IDL} -DXP_UNIX -DXP_MACOSX dsd${T}-module.cpp

        XR_PATH=${DP_XR_SDK_PATH}
        XR_SDK=${XR_PATH}/sdk
        XR_BIN=${XR_PATH}/bin
        XR_IDL=${XR_PATH}/idl
        ${CC} -arch ppc -fshort-wchar -w -c -o dsd${T}-module-darwin-ppc.o -I ${XR_SDK}/include -I ${XR_PATH}/include/xpcom -I ${XR_IDL} -DXP_UNIX -DXP_MACOSX dsd${T}-module.cpp
    else
	DSDM_PATH=/home/atj/bonjourfoxy/src/manager

        XR_PATH=${UL_XR_SDK_PATH}
        XR_SDK=${XR_PATH}/sdk
        XR_BIN=${XR_PATH}/bin
        XR_IDL=${XR_PATH}/idl

        ${CC} -fshort-wchar -w -c -o dsd${T}-module-linux.o -I ${XR_SDK}/include -I ${XR_PATH}/include/xpcom -I ${XR_IDL} -DXP_UNIX dsd${T}-module.cpp            
    fi
    
}

buildlib() {
    if [ ${UNAME} == "DARWIN" ]; then
        DSDM_PATH=/Users/atj/Projects/bonjourfoxy/src/manager

        XR_PATH=${DI_XR_SDK_PATH}
        XR_SDK=${XR_PATH}/sdk
        XR_BIN=${XR_PATH}/bin
        XR_IDL=${XR_PATH}/idl
        
        ${CC} -L${XR_SDK}/lib -L${XR_BIN} -Wl,-executable_path, -fshort-wchar -dynamiclib -o dsd${T}-darwin-intel.dylib dsd${T}-impl-darwin-intel.o dsd${T}-module-darwin-intel.o -lxpcomglue_s -lxpcom -lnspr4

        XR_PATH=${DP_XR_SDK_PATH}
        XR_SDK=${XR_PATH}/sdk
        XR_BIN=${XR_PATH}/bin
        XR_IDL=${XR_PATH}/idl
        ${CC} -arch ppc -L${XR_SDK}/lib -L${XR_BIN} -Wl,-executable_path, -fshort-wchar -dynamiclib -o dsd${T}-darwin-ppc.dylib dsd${T}-impl-darwin-ppc.o dsd${T}-module-darwin-ppc.o -lxpcomglue_s -lxpcom -lnspr4
    else
	DSDM_PATH=/home/atj/bonjourfoxy/src/manager

        XR_PATH=${UL_XR_SDK_PATH}
        XR_SDK=${XR_PATH}/sdk
        XR_BIN=${XR_PATH}/bin
        XR_IDL=${XR_PATH}/idl

        ${CC} -shared -Wl,-z,defs -L${XR_SDK}/lib -L${XR_BIN} -Wl,-rpath-link,${XR_SDK} -fshort-wchar -dynamiclib -o dsd${T}-linux.so dsd${T}-impl-linux.o dsd${T}-module-linux.o -lxpcomglue_s -lxpcom -lnspr4 -ldns_sd

    fi
}

dolipo()    {
    if [ ${UNAME} == "DARWIN" ]; then
        lipo -create dsd${T}-darwin-{intel,ppc}.dylib -output dsd${T}-darwin.dylib
    fi
}

cd ${BASE_DIR}
for T in ${TARGETS}; do
    cd ${T}
    if [ -f *.js ]; then
        echo ${T} contains `ls *.js` so just building XPT
        buildxpt        
    else
        echo ${T} is assumed to contain binary targets
        buildxpt
        buildimpl
        buildmodule
        buildlib
        # dolipo
    fi
    cd -
done
