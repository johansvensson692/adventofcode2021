#!/bin/sh
if [ ! $# -eq 1 ]; then
    echo "Only one argument"
    return 1
fi
cp -r template ${1}
mv ${1}/dayxx.cc ${1}/${1}.cc
sed -i "s/dayxx/${1}/g" ${1}/Makefile
