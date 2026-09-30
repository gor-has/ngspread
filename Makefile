# ngspread replacement Makefile
#
# Builds the Spread daemon plus libspread as shared/static libraries and
# installs the public header and pkg-config metadata.

PREFIX      ?= /usr/local
DESTDIR     ?=
LIBDIR      ?= $(PREFIX)/lib
INCLUDEDIR  ?= $(PREFIX)/include/ngspread
PKGCONFIGDIR ?= $(LIBDIR)/pkgconfig
BINDIR      ?= $(PREFIX)/bin

CC          ?= cc
AR          ?= ar
RANLIB      ?= ranlib
INSTALL     ?= install
PKG_CONFIG  ?= pkg-config

CFLAGS      ?= -O2 -g
CFLAGS      += -Wall -Wextra -fPIC


# CPPFLAGS    += -Iinclude -Ilibspread -Ilibspread-util/src -Istdutil/src

CPPFLAGS := \
	-Iinclude \
	-Ilibspread \
	-Ilibspread-util/include \
	-Ilibspread-util/src \
	-Istdutil/src \
	-Idaemon \
	$(shell pkg-config --cflags glib-2.0)



GLIB_CFLAGS := $(shell $(PKG_CONFIG) --cflags glib-2.0 2>/dev/null)
GLIB_LIBS   := $(shell $(PKG_CONFIG) --libs glib-2.0 2>/dev/null)
CPPFLAGS    += $(GLIB_CFLAGS)

LIBSPREAD_OBJECTS = \
	libspread/sp.o \
	libspread/fl.o \
	libspread/scatp.o

LIBSPREAD_UTIL_OBJECTS = \
	libspread-util/src/alarm.o \
	libspread-util/src/events.o \
	libspread-util/src/memory.o \
	libspread-util/src/data_link.o \
	libspread-util/src/spu_addr.o

# stdutil is retained as part of the ngspread build. Add/remove objects here
# to match the files in stdutil/src if the local tree differs.
STDUTIL_SOURCES := $(wildcard stdutil/src/*.c)
STDUTIL_OBJECTS := $(STDUTIL_SOURCES:.c=.o)

SPREAD_OBJECTS := $(wildcard daemon/*.o)

LIBSPREAD_STATIC = libspread/libspread.a
LIBSPREAD_SHARED = libspread/libspread.so

.PHONY: all libraries daemon install uninstall clean check check-build check-install

all: libraries daemon

libraries: $(LIBSPREAD_STATIC) $(LIBSPREAD_SHARED)

$(LIBSPREAD_STATIC): $(LIBSPREAD_OBJECTS) $(LIBSPREAD_UTIL_OBJECTS) $(STDUTIL_OBJECTS)
	$(AR) rcs $@ $^
	$(RANLIB) $@

$(LIBSPREAD_SHARED): $(LIBSPREAD_OBJECTS) $(LIBSPREAD_UTIL_OBJECTS) $(STDUTIL_OBJECTS)
	$(CC) -shared -Wl,-soname,libspread.so -o $@ $^ $(GLIB_LIBS) -ldl

# The existing ngspread tree has historically built the daemon from daemon/.
# Keep daemon compilation delegated to its existing object set where possible.
daemon:
	@echo "Libraries built. Build the Spread daemon with the repository's current daemon target/rules if required."

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

ngspread.pc: ngspread.pc.in
	sed \
		-e 's|@PREFIX@|$(PREFIX)|g' \
		-e 's|@LIBDIR@|$(LIBDIR)|g' \
		-e 's|@INCLUDEDIR@|$(PREFIX)/include|g' \
		$< > $@

install: libraries ngspread.pc
	$(INSTALL) -d $(DESTDIR)$(LIBDIR)
	$(INSTALL) -d $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -d $(DESTDIR)$(PKGCONFIGDIR)
	$(INSTALL) -m 755 $(LIBSPREAD_SHARED) $(DESTDIR)$(LIBDIR)/
	$(INSTALL) -m 644 $(LIBSPREAD_STATIC) $(DESTDIR)$(LIBDIR)/
	$(INSTALL) -m 644 include/ngspread/sp.h $(DESTDIR)$(INCLUDEDIR)/sp.h
	$(INSTALL) -m 644 ngspread.pc $(DESTDIR)$(PKGCONFIGDIR)/ngspread.pc
	@echo
	@echo "Installed ngspread under $(DESTDIR)$(PREFIX)"
	@echo "For a real system install, run ldconfig if your platform requires it."

uninstall:
	rm -f $(DESTDIR)$(LIBDIR)/libspread.so
	rm -f $(DESTDIR)$(LIBDIR)/libspread.a
	rm -f $(DESTDIR)$(PKGCONFIGDIR)/ngspread.pc
	rm -f $(DESTDIR)$(INCLUDEDIR)/sp.h
	-rmdir $(DESTDIR)$(INCLUDEDIR) 2>/dev/null || true

check: ngspread.pc
	PKG_CONFIG_PATH="$(CURDIR):$$PKG_CONFIG_PATH" $(PKG_CONFIG) --cflags --libs ngspread

check-build: all check
	@echo "=== Checking build products ==="

	@test -s libspread/libspread.a || \
		{ echo "ERROR: libspread/libspread.a missing"; exit 1; }

	@test -s libspread/libspread.so || \
		{ echo "ERROR: libspread/libspread.so missing"; exit 1; }

	@test -s include/ngspread/sp.h || \
		{ echo "ERROR: include/ngspread/sp.h missing"; exit 1; }

	@echo "Checking shared library type..."
	@file libspread/libspread.so | grep -q "shared object" || \
		{ echo "ERROR: libspread.so is not a shared object"; exit 1; }

	@echo "Checking shared library dependencies..."
	@ldd libspread/libspread.so

	@echo "Checking exported Spread symbols..."
	@nm -D --defined-only libspread/libspread.so | \
		grep -q ' SP_connect' || \
		{ echo "ERROR: SP_connect is not exported"; exit 1; }

	@nm -D --defined-only libspread/libspread.so | \
		grep -q ' SP_receive' || \
		{ echo "ERROR: SP_receive is not exported"; exit 1; }

	@nm -D --defined-only libspread/libspread.so | \
		grep -q ' SP_multicast' || \
		{ echo "ERROR: SP_multicast is not exported"; exit 1; }

	@echo "=== ngspread build looks OK ==="


check-install:
	@echo "=== Checking installed ngspread ==="

	@test -s $(DESTDIR)$(LIBDIR)/libspread.so || \
		{ echo "ERROR: installed libspread.so missing"; exit 1; }

	@test -s $(DESTDIR)$(LIBDIR)/libspread.a || \
		{ echo "ERROR: installed libspread.a missing"; exit 1; }

	@test -s $(DESTDIR)$(INCLUDEDIR)/sp.h || \
		{ echo "ERROR: installed sp.h missing"; exit 1; }

	@test -s $(DESTDIR)$(PKGCONFIGDIR)/ngspread.pc || \
		{ echo "ERROR: installed ngspread.pc missing"; exit 1; }

	@echo "Checking installed pkg-config metadata..."
	@$(PKG_CONFIG) --exists ngspread || \
		{ echo "ERROR: pkg-config cannot find ngspread"; exit 1; }

	@$(PKG_CONFIG) --cflags --libs ngspread

	@echo "Checking installed shared library..."
	@ldd $(DESTDIR)$(LIBDIR)/libspread.so

	@echo "Checking installed API..."
	@nm -D --defined-only $(DESTDIR)$(LIBDIR)/libspread.so | \
		grep -q ' SP_connect' || \
		{ echo "ERROR: SP_connect missing"; exit 1; }

	@echo "=== Installed ngspread looks OK ==="


clean:
	rm -f $(LIBSPREAD_OBJECTS) $(LIBSPREAD_UTIL_OBJECTS) $(STDUTIL_OBJECTS)
	rm -f $(LIBSPREAD_STATIC) $(LIBSPREAD_SHARED) ngspread.pc
