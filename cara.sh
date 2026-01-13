#!/bin/bash

# Exit immediately if any command fails
set -e

# Remove the build directory if it exists
if [ -d build_cara ]; then rm -rf build_cara; fi

mkdir build_cara
cd build_cara

echo ''
echo '------------------------'
echo '--------- Cara ---------'
echo '----- #SAT  solver -----'
echo '------------------------'
echo ''

# Release
mkdir Release
cd Release
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release -D BUILD_CARA=True "../.."
make -j8

cd ..

# Debug
mkdir Debug
cd Debug
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D BUILD_CARA=True "../.."
make -j8

cd ..

# Test
mkdir Test
cd Test
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D BUILD_CARA=True -D BUILD_TEST=True "../.."
make -j8

cd ..
