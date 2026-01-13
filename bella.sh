#!/bin/bash

# Exit immediately if any command fails
set -e

# Remove the build directory if it exists
if [ -d build_bella ]; then rm -rf build_bella; fi

mkdir build_bella
cd build_bella

echo ''
echo '-------------------------'
echo '--------- Bella ---------'
echo '-- knowledge  compiler --'
echo '-------------------------'
echo ''

# Release
mkdir Release
cd Release
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release -D BUILD_BELLA=True "../.."
make -j8

cd ..

# Debug
mkdir Debug
cd Debug
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D BUILD_BELLA=True "../.."
make -j8

cd ..

# Test
mkdir Test
cd Test
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D BUILD_BELLA=True -D BUILD_TEST=True "../.."
make -j8

cd ..
