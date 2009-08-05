#!/bin/bash
rel=${1}
dir=scratch/${rel}
if [ ! $1 ]; then
    echo "No release provided"
    exit 1
elif [ -d ${dir} ]; then
    echo "${dir} already exists - continue anyway?"
    read confirm
    if [ ${confirm} != "y" ]; then
        echo exiting
        exit 0
    fi
fi
mkdir -pv ${dir}
cp -r ext/* ${dir}
mkdir -pv ${dir}/components
find src -name "*.xpt" -exec cp {} ${dir}/components \;
find src -name "*.js" -exec cp {} ${dir}/components \;
mkdir -pv ${dir}/platform/Linux/components
find src -name "*.so" -exec cp {} ${dir}/platform/Linux/components \;
mkdir -pv ${dir}/platform/Darwin/components
find src -name "*darwin.dylib" -exec cp {} ${dir}/platform/Darwin/components \;
mkdir -pv ${dir}/platform/WINNT/components
find src -name "*.dll" -exec cp {} ${dir}/platform/WINNT/components \;
