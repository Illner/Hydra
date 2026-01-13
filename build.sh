#!/bin/bash

# Bella compiler
if [ -x bella.sh ]; then
  ./bella.sh
elif [ -f bella.sh ]; then
    echo 'Warning: ./bella.sh exists but is not executable.'
else
    echo 'Warning: ./bella.sh not found, skipping Bella.'
fi

# Cara solver
if [ -x cara.sh ]; then
  ./cara.sh
elif [ -f cara.sh ]; then
    echo 'Warning: ./cara.sh exists but is not executable.'
else
    echo 'Warning: ./cara.sh not found, skipping Cara.'
fi
