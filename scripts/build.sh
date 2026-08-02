#!/bin/bash

# Bella
if [ -x ./scripts/bella.sh ]; then
  ./scripts/bella.sh "$@"
elif [ -f ./scripts/bella.sh ]; then
    echo "WARNING: ./scripts/bella.sh exists but is not executable; run chmod +x ./scripts/bella.sh"
else
    echo "WARNING: ./scripts/bella.sh not found, skipping Bella."
fi

# Cara
if [ -x ./scripts/cara.sh ]; then
  ./scripts/cara.sh "$@"
elif [ -f ./scripts/cara.sh ]; then
    echo "WARNING: ./scripts/cara.sh exists but is not executable; run chmod +x ./scripts/cara.sh"
else
    echo "WARNING: ./scripts/cara.sh not found, skipping Cara."
fi
