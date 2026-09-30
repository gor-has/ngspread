ngspread installation kit
=========================

This kit is intended for the current ngspread source tree whose public API is
include/sp.h and whose core objects include libspread/sp.c, fl.c and scatp.c,
plus the libspread-util sources.

1. Copy these files to the ngspread repository root.

2. Prepare the namespaced public-header directory:

       ./prepare-layout.sh

   This creates:

       include/ngspread/sp.h

3. Build:

       make clean
       make

4. Test pkg-config generation before installation:

       make check

5. Install:

       sudo make install
       sudo ldconfig

   Installed files are:

       /usr/local/include/ngspread/sp.h
       /usr/local/lib/libspread.so
       /usr/local/lib/libspread.a
       /usr/local/lib/pkgconfig/ngspread.pc

6. Verify:

       pkg-config --cflags --libs ngspread

   Expected form:

       -I/usr/local/include/ngspread -L/usr/local/lib -lspread -ldl

7. Application source:

       #include <sp.h>

   Compile/link:

       cc program.c -o program $(pkg-config --cflags --libs ngspread)

   Because ngspread.pc supplies -I/usr/local/include/ngspread, <sp.h> remains
   source-compatible with the historical API while avoiding installation of a
   generic sp.h directly in /usr/local/include.

Packaging/staging
-----------------

DESTDIR is supported:

       make install DESTDIR=/tmp/ngspread-package

A convenience wrapper is also included:

       sudo ./install-layout.sh

Notes
-----

The replacement Makefile deliberately keeps the installed library name
libspread.so/libspread.a for source/link compatibility with existing programs.
The package identity used by pkg-config is "ngspread".

The daemon portion of the repository has changed during the modernization work.
The supplied Makefile therefore focuses on the reusable library/install target
rather than guessing a daemon object list. Existing daemon build rules can be
merged into the `daemon` target once the current daemon source list is fixed.
