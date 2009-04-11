#!/bin/bash

CC=g++
UNAME=`uname -s 2>/dev/null | tr 'a-z' 'A-Z' || echo not`
UNAMEM=`uname -m || echo not`
UL_XR_SDK_PATH=/usr/include/xulrunner-1.9.0.8
DP_XR_SDK_PATH=/Developer/xulrunner-1.9.0.6-ppc
DI_XR_SDK_PATH=/Developer/xulrunner-1.9.0.6-intel
BASE_DIR=`dirname $0`
TARGETS=`cd ${BASE_DIR}; for i in * ; do if [ -d $i ]; then echo $i ; fi ; done`

buildxpt()  {
    if [ ${UNAME} == "DARWIN" ]; then
        XR_PATH=${DI_XR_SDK_PATH}
        XPIDL=${XR_PATH}/bin/xpidl
        DSDM_PATH=/Users/atj/Projects/bonjourfoxy/src/manager
        ${XPIDL} -m header -I${XR_PATH}/idl -I ${DSDM_PATH} *.idl
    else
        XR_PATH=${UL_XR_SDK_PATH}
        XPIDL=/usr/lib/xulrunner-1.9.0.8/xpidl
        IDL=/usr/share/idl/xulrunner-1.9.0.8
        DSDM_PATH=/home/atj/bonjourfoxy/src/manager
        ${XPIDL} -m header -I${XR_PATH}/sdk/idl -I ${DSDM_PATH} -I ${IDL}/stable -I ${IDL}/unstable *.idl
    fi
}

buildimpl() {
    if [ ${UNAME} == "DARWIN" ]; then
        DSDM_PATH=/Users/atj/Projects/bonjourfoxy/src/manager
        XR_PATH=${DI_XR_SDK_PATH}
        ${CC} -fshort-wchar -w -c -o dsd${T}-impl-darwin-intel.o -I ${XR_PATH}/sdk/include -I ${XR_PATH}/include/xpcom -I ${XR_PATH}/idl -DXP_UNIX -DXP_MACOSX -I ${DSDM_PATH} dsd${T}-impl.cpp
        XR_PATH=${DP_XR_SDK_PATH}
        ${CC} -arch ppc -fshort-wchar -w -c -o dsd${T}-impl-darwin-ppc.o -I ${XR_PATH}/sdk/include -I ${XR_PATH}/include/xpcom -I ${XR_PATH}/idl -DXP_UNIX -DXP_MACOSX -I ${DSDM_PATH} dsd${T}-impl.cpp
    else
        DSDM_PATH=/home/atj/bonjourfoxy/src/manager
        XR_PATH=${UL_XR_SDK_PATH}
        if [ ${UNAMEM} == "x86_64" ]; then
            ${CC} -fPIC -fshort-wchar -w -c -o dsd${T}-impl-linux64.o -I /usr/include/nspr -I ${XR_PATH}/stable -I ${XR_PATH}/unstable -DXP_UNIX -I ${DSDM_PATH} dsd${T}-impl.cpp
        else
            ${CC} -fshort-wchar -w -c -o dsd${T}-impl-linux.o -I /usr/include/nspr -I ${XR_PATH}/stable -I ${XR_PATH}/unstable -DXP_UNIX -I ${DSDM_PATH} dsd${T}-impl.cpp
        fi
    fi
}

buildmodule() {
    if [ ${UNAME} == "DARWIN" ]; then
        DSDM_PATH=/Users/atj/Projects/bonjourfoxy/src/manager
        XR_PATH=${DI_XR_SDK_PATH}
        ${CC} -fshort-wchar -w -c -o dsd${T}-module-darwin-intel.o -I ${XR_PATH}/sdk/include -I ${XR_PATH}/include/xpcom -I ${XR_PATH}/idl -DXP_UNIX -DXP_MACOSX dsd${T}-module.cpp
        XR_PATH=${DP_XR_SDK_PATH}
        ${CC} -arch ppc -fshort-wchar -w -c -o dsd${T}-module-darwin-ppc.o -I ${XR_PATH}/sdk/include -I ${XR_PATH}/include/xpcom -I ${XR_PATH}/idl -DXP_UNIX -DXP_MACOSX dsd${T}-module.cpp
    else
        DSDM_PATH=/home/atj/bonjourfoxy/src/manager
        XR_PATH=${UL_XR_SDK_PATH}   
        if [ ${UNAMEM} == "x86_64" ]; then         
            ${CC} -fPIC -fshort-wchar -w -c -o dsd${T}-module-linux64.o -I /usr/include/nspr -I ${XR_PATH}/stable -I ${XR_PATH}/unstable -DXP_UNIX dsd${T}-module.cpp            
        else
            ${CC} -fshort-wchar -w -c -o dsd${T}-module-linux.o -I /usr/include/nspr -I ${XR_PATH}/stable -I ${XR_PATH}/unstable -DXP_UNIX dsd${T}-module.cpp            
        fi
    fi
    
}

buildlib() {
    if [ ${UNAME} == "DARWIN" ]; then
        DSDM_PATH=/Users/atj/Projects/bonjourfoxy/src/manager
        XR_PATH=${DI_XR_SDK_PATH}
        ${CC} -L${XR_PATH}/sdk/lib -L${XR_PATH}/bin -Wl,-executable_path, -fshort-wchar -dynamiclib -o dsd${T}-darwin-intel.dylib dsd${T}-impl-darwin-intel.o dsd${T}-module-darwin-intel.o -lxpcomglue_s -lxpcom -lnspr4
        XR_PATH=${DP_XR_SDK_PATH}
        ${CC} -arch ppc -L${XR_PATH}/sdk/lib -L${XR_PATH}/bin -Wl,-executable_path, -fshort-wchar -dynamiclib -o dsd${T}-darwin-ppc.dylib dsd${T}-impl-darwin-ppc.o dsd${T}-module-darwin-ppc.o -lxpcomglue_s -lxpcom -lnspr4
    else
        DSDM_PATH=/home/atj/bonjourfoxy/src/manager
        XR_PATH=${UL_XR_SDK_PATH}
        if [ ${UNAMEM} == "x86_64" ]; then
            ${CC} -shared -Wl,-z,defs -L/usr/lib/xulrunner-devel-1.9.0.8/sdk/lib -L${XR_PATH}/bin -Wl,-rpath-link,${XR_PATH}/sdk -fshort-wchar -dynamiclib -o dsd${T}-linux64.so dsd${T}-impl-linux64.o dsd${T}-module-linux64.o -lxpcomglue_s -lxpcom -lnspr4 -ldns_sd
        else
            ${CC} -shared -Wl,-z,defs -L/usr/lib/xulrunner-devel-1.9.0.8/sdk/lib -L${XR_PATH}/bin -Wl,-rpath-link,${XR_PATH}/sdk -fshort-wchar -dynamiclib -o dsd${T}-linux.so dsd${T}-impl-linux.o dsd${T}-module-linux.o -lxpcomglue_s -lxpcom -lnspr4 -ldns_sd
        fi
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
        echo buildxpt
        buildxpt
        echo buildimpl
        buildimpl
        echo buildmodule
        buildmodule
        echo buildlib
        buildlib
        dolipo
    fi
    cd -
done
