#!/bin/bash
if find . | grep -q '\.uf2' && find . | grep -q '\.img'; then
    mkdir -p build
    cp ./Kernel/platform/platform-rpipico/build/fuzix.uf2 build/
    cp ./Kernel/platform/platform-rpipico/filesystem.uf2 build/
    cp ./Kernel/platform/platform-rpipico/filesystem.img build/
else
    echo 'No build files found'
fi
