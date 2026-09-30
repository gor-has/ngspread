#!/bin/sh
set -eu

# Convenience wrapper. PREFIX and DESTDIR may be overridden, for example:
#   PREFIX=/opt/ngspread ./install-layout.sh
#   DESTDIR=/tmp/package-root ./install-layout.sh

PREFIX=${PREFIX:-/usr/local}
DESTDIR=${DESTDIR:-}

make
make install PREFIX="$PREFIX" DESTDIR="$DESTDIR"
