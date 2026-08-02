#!/bin/bash

# Guard against accidentally running this directly instead of sourcing it
if [ "${BASH_SOURCE[0]}" = "${0}" ]; then
    echo "ERROR: ./scripts/parse_args.sh is meant to be sourced, not executed directly!" >&2
    echo "NOTE: execute ./scripts/bella.sh or ./scripts/cara.sh instead." >&2
    exit 1
fi

# Static linking (default: off)
export BUILD_STATIC=False     # --static

# Build mode(s) (default: all three)
export BUILD_RELEASE=false    # --release
export BUILD_DEBUG=false      # --debug
export BUILD_TEST=false       # --test
AT_LEAST_ONE_BUILD_MODE=false

for arg in "$@"; do
    case "$arg" in
        --static)  BUILD_STATIC=True ;;
        --release) BUILD_RELEASE=true; AT_LEAST_ONE_BUILD_MODE=true ;;
        --debug)   BUILD_DEBUG=true;   AT_LEAST_ONE_BUILD_MODE=true ;;
        --test)    BUILD_TEST=true;    AT_LEAST_ONE_BUILD_MODE=true ;;
        --all)     BUILD_RELEASE=true; BUILD_DEBUG=true; BUILD_TEST=true; AT_LEAST_ONE_BUILD_MODE=true ;;
        *) echo "WARNING: unrecognized argument '$arg' is ignored." ;;
    esac
done

# No build mode given at all -> build all three modes
if [ "$AT_LEAST_ONE_BUILD_MODE" = false ]; then
    BUILD_RELEASE=true
    BUILD_DEBUG=true
    BUILD_TEST=true
fi
