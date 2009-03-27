#!/bin/bash
cd `dirname $0`
rm -fv bonjourfoxy.xpi
find .                  \
! -path "*src*"         \
! -path "*git*"         \
! -name "update.rdf"     \
! -name "*.DS_Store"    \
! -name "*.sh"          \
! -name "README"        \
| zip bonjourfoxy.xpi -@
