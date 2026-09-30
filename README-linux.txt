NGspread Linux/systemd installation - version 3
================================================

Installed layout:

    /usr/local/sbin/spread        NGspread daemon
    /usr/local/bin/spuser         interactive Spread client
    /etc/ngspread/spread.conf     configuration
    /etc/systemd/system/ngspread.service
    /var/run/spread               runtime/chroot directory

The installer creates the system account:

    spread:spread

Before installation, build both:

    spread
    spuser

and provide the real configuration as:

    ./spread.conf

Install:

    sudo make -f Makefile.linux install

Start:

    sudo systemctl start ngspread

Status:

    sudo systemctl status ngspread

Logs:

    sudo journalctl -u ngspread -n 100 --no-pager

The installed client can then be invoked simply as:

    spuser

Important implementation notes
------------------------------

Linux linking needs -ldl because events.c uses dladdr().

The parsed -c/--config-file value must reach Conf_init(). The working call in
daemon/spread.c is:

    Conf_init(config_file, My_name);

The existing /etc/ngspread/spread.conf is not overwritten.

systemd RuntimeDirectory=spread recreates /run/spread. On normal Linux
systems /var/run points to /run.

The current configuration may still use /tmp/4803 for the AF_UNIX socket.
Moving this into a protected runtime directory remains a later improvement.

FreeBSD service installation should be kept separately in Makefile.bsd.
