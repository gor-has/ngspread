NGspread Linux/systemd installation
===================================

Files
-----

Makefile.linux
    Installs the already-built spread daemon, configuration file and
    systemd service.

ngspread.service
    systemd unit for NGspread.

spread.conf.example
    Placeholder/example configuration file. Replace its contents with
    the actual NGspread/Spread configuration before starting the service.


Installed locations
-------------------

    /usr/local/sbin/spread
    /etc/ngspread/spread.conf
    /etc/systemd/system/ngspread.service


Installation
------------

First build NGspread so that ./spread exists and is executable.

Copy Makefile.linux and ngspread.service to the NGspread source directory.
Create or copy the real configuration as:

    ./spread.conf

Then install:

    sudo make -f Makefile.linux install

The installation enables ngspread.service but deliberately does NOT start it.

Review:

    sudo vi /etc/ngspread/spread.conf

Start and inspect:

    sudo systemctl start ngspread
    sudo systemctl status ngspread

Logs:

    sudo journalctl -u ngspread -n 100

or:

    sudo make -f Makefile.linux logs


Configuration option
--------------------

NGspread accepts:

    -c, --config-file     Configuration file.

The systemd unit therefore starts it as:

    /usr/local/sbin/spread -c /etc/ngspread/spread.conf

There is no daemon/background option in the current command-line interface.
The systemd service consequently uses Type=simple and runs spread in the
foreground under systemd supervision.


Useful Makefile targets
-----------------------

    sudo make -f Makefile.linux install
    sudo make -f Makefile.linux enable
    sudo make -f Makefile.linux start
    sudo make -f Makefile.linux stop
    sudo make -f Makefile.linux restart
    sudo make -f Makefile.linux status
    sudo make -f Makefile.linux logs
    sudo make -f Makefile.linux uninstall


Notes
-----

The install-conf target does not overwrite an existing
/etc/ngspread/spread.conf.

The uninstall target disables/removes the systemd service but deliberately
leaves the daemon binary and configuration file in place.

A separate Makefile.bsd can later implement the FreeBSD rc.d installation.
