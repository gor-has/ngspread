ngspread Makefile/service layout
================================

Makefile
    Top-level orchestration only.

Makefile.libs
    Builds and installs the ngspread client library.

Makefile.prog
    Builds and installs spread and spuser.

Makefile.service-linux
    Creates the spread service account/directories, preserves an existing
    /etc/ngspread/spread.conf, installs service/service.linux as
    /etc/systemd/system/ngspread.service, reloads systemd and enables it.

Makefile.service-freebsd
    Creates the spread service account/directories, preserves an existing
    /usr/local/etc/ngspread/spread.conf, installs service/service.freebsd as
    /usr/local/etc/rc.d/ngspread and enables it with sysrc.

service/service.linux
    Source form of the Linux systemd unit.

service/service.freebsd
    Source form of the FreeBSD rc.d script.  The pre-start routine recreates
    /var/run/spread after reboot.

Typical commands
----------------

Build everything:

    make

Install binaries/libraries:

    sudo make install

Install Linux service:

    sudo make service-linux

Install FreeBSD service:

    sudo make service-freebsd
