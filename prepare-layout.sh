#!/bin/sh
set -eu

# Run from the ngspread repository root.
# This script only prepares the new directory layout and copies the public API.

if [ ! -f include/sp.h ] || [ ! -d libspread ]; then
    echo "Run this script from the ngspread repository root." >&2
    exit 1
fi

mkdir -p include/ngspread

# Keep the historical sp.h name, but install it in an ngspread namespace.
cp -p include/sp.h include/ngspread/sp.h

echo "Prepared include/ngspread/sp.h"
echo "Review include/ngspread/ and add any further public headers before make install."
