#!/bin/sh
rel=$1
out=~/Projects/bonjourfoxy/sdk/archive
pre=xulrunner-${rel}.en-US
win32=${pre}.win32.sdk.zip
linux=${pre}.linux-i686.sdk.tar.bz2
macppc=${pre}.mac-powerpc.sdk.tar.bz2
macintel=${pre}.mac-i386.sdk.tar.bz2
mirrorbase=http://mirror.internode.on.net/pub/mozilla/xulrunner/releases
mirrorrel=${mirrorbase}/${rel}/sdk/
if [ ! $1 ]; then
    echo "No release provided"
    exit 1
elif [ `lynx -dump ${mirrorbase} | grep -c ${rel}` -ne 2 ]; then
    echo "Check version supplied"
    exit 1
fi
wget -c -P ${out} ${mirrorrel}{${linux},${win32},${macppc},${macintel}}