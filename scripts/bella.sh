#!/bin/bash

# Exit immediately if any command fails
set -e

if [ ! -d scripts ]; then
  echo "ERROR: the script must be executed from the repository root: ./scripts/bella.sh" >&2
  exit 1
fi

# Parse the arguments
source ./scripts/parse_args.sh "$@"

mkdir -p build_bella
cd build_bella

echo ""
echo "-------------------------"
echo "--------- Bella ---------"
echo "-- knowledge  compiler --"
echo "-------------------------"
echo ""

# Release
if [ "$BUILD_RELEASE" = true ]; then
  # Remove the release directory if it exists
  if [ -d Release ]; then rm -rf Release; fi

  mkdir Release
  cd Release
  cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release -D BUILD_BELLA=True -D BUILD_STATIC="$BUILD_STATIC" "../.."
  make -j8

  cd ..
fi

# Debug
if [ "$BUILD_DEBUG" = true ]; then
  # Remove the debug directory if it exists
  if [ -d Debug ]; then rm -rf Debug; fi

  mkdir Debug
  cd Debug
  cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D BUILD_BELLA=True -D BUILD_STATIC="$BUILD_STATIC" "../.."
  make -j8

  cd ..
fi

# Test
if [ "$BUILD_TEST" = true ]; then
  # Remove the test directory if it exists
  if [ -d Test ]; then rm -rf Test; fi

  mkdir Test
  cd Test
  cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D BUILD_BELLA=True -D BUILD_TEST=True -D BUILD_STATIC="$BUILD_STATIC" "../.."
  make -j8

  cd ..
fi

cd ..
