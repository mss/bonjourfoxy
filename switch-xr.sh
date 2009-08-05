#!/bin/bash
rel=${1}
archivedir=~/Projects/bonjourfoxy/sdk/archive
outbase=~/Projects/bonjourfoxy/sdk
pre=xulrunner-${rel}.en-US
win32=${pre}.win32.sdk.zip
win32dir=${outbase}/win32
linux=${pre}.linux-i686.sdk.tar.bz2
linuxdir=${outbase}/linux
macppc=${pre}.mac-powerpc.sdk.tar.bz2
macppcdir=${outbase}/macppc
macintel=${pre}.mac-i386.sdk.tar.bz2
macinteldir=${outbase}/macintel
if [ ! $1 ]; then
    echo "No release provided"
    exit 1
elif [ `ls ${archivedir}/{${win32},${linux},${macppc},${macintel}} | wc -l` -ne 4 ]; then
    echo "Check version supplied"
    exit 1
fi
echo ${win32} -\> ${win32dir}
mkdir -p ${win32dir}
unzip -q -o ${archivedir}/${win32} -d ${win32dir}
echo ${linux} -\> ${linuxdir}
mkdir -p ${linuxdir}
tar -xjf ${archivedir}/${linux} -C ${linuxdir}
echo ${macppc} -\> ${macppcdir}
mkdir -p ${macppcdir}
tar -xjf ${archivedir}/${macppc} -C ${macppcdir}
echo ${macintel} -\> ${macinteldir}
mkdir -p ${macinteldir}
tar -xjf ${archivedir}/${macintel} -C ${macinteldir}