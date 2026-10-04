# Top-level ngspread build orchestration.
#
# This Makefile contains no daemon target.  The actual build logic is kept in:
#
#   Makefile.libs
#   Makefile.prog
#
# Platform-specific service installation is kept in:
#
#   Makefile.service-linux
#   Makefile.service-freebsd

.PHONY: all libs prog clean install install-libs install-prog \
        service-linux service-freebsd uninstall-service-linux \
        uninstall-service-freebsd

all: libs prog

libs:
	$(MAKE) -f Makefile.libs

prog:
	$(MAKE) -f Makefile.prog

clean:
	$(MAKE) -f Makefile.prog clean
	$(MAKE) -f Makefile.libs clean

install: install-libs install-prog

install-libs:
	$(MAKE) -f Makefile.libs install

install-prog:
	$(MAKE) -f Makefile.prog install

service-linux:
	$(MAKE) -f Makefile.service-linux install

service-freebsd:
	$(MAKE) -f Makefile.service-freebsd install

uninstall-service-linux:
	$(MAKE) -f Makefile.service-linux uninstall

uninstall-service-freebsd:
	$(MAKE) -f Makefile.service-freebsd uninstall
