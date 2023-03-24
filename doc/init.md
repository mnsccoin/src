Sample init scripts and service configuration for mnsavingsd
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/mnsavingsd.service:    systemd service unit configuration
    contrib/init/mnsavingsd.openrc:     OpenRC compatible SysV style init script
    contrib/init/mnsavingsd.openrcconf: OpenRC conf.d file
    contrib/init/mnsavingsd.conf:       Upstart service configuration file
    contrib/init/mnsavingsd.init:       CentOS compatible SysV style init script

Service User
---------------------------------

All three Linux startup configurations assume the existence of a "mnsavings" user
and group.  They must be created before attempting to use these scripts.
The macOS configuration assumes mnsavingsd will be set up for the current user.

Configuration
---------------------------------

At a bare minimum, mnsavingsd requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, mnsavingsd will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that mnsavingsd and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If mnsavingsd is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running mnsavingsd without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see contrib/debian/examples/mnsavings.conf.

Paths
---------------------------------

### Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              /usr/bin/mnsavingsd
Configuration file:  /etc/mnsavings/mnsavings.conf
Data directory:      /var/lib/mnsavingsd
PID file:            `/var/run/mnsavingsd/mnsavingsd.pid` (OpenRC and Upstart) or `/run/mnsavingsd/mnsavingsd.pid` (systemd)
Lock file:           `/var/lock/subsys/mnsavingsd` (CentOS)

The configuration file, PID directory (if applicable) and data directory
should all be owned by the mnsavings user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
mnsavings user and group.  Access to mnsavings-cli and other mnsavingsd rpc clients
can then be controlled by group membership.

NOTE: When using the systemd .service file, the creation of the aforementioned
directories and the setting of their permissions is automatically handled by
systemd. Directories are given a permission of 710, giving the mnsavings group
access to files under it _if_ the files themselves give permission to the
mnsavings group to do so (e.g. when `-sysperms` is specified). This does not allow
for the listing of files under the directory.

NOTE: It is not currently possible to override `datadir` in
`/etc/mnsavings/mnsavings.conf` with the current systemd, OpenRC, and Upstart init
files out-of-the-box. This is because the command line options specified in the
init files take precedence over the configurations in
`/etc/mnsavings/mnsavings.conf`. However, some init systems have their own
configuration mechanisms that would allow for overriding the command line
options specified in the init files (e.g. setting `BITCOIND_DATADIR` for
OpenRC).

### macOS

Binary:              `/usr/local/bin/mnsavingsd`
Configuration file:  `~/Library/Application Support/MNSAVINGS/mnsavings.conf`
Data directory:      `~/Library/Application Support/MNSAVINGS`
Lock file:           `~/Library/Application Support/MNSAVINGS/.lock`

Installing Service Configuration
-----------------------------------

### systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start mnsavingsd` and to enable for system startup run
`systemctl enable mnsavingsd`

NOTE: When installing for systemd in Debian/Ubuntu the .service file needs to be copied to the /lib/systemd/system directory instead.

### OpenRC

Rename mnsavingsd.openrc to mnsavingsd and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/mnsavingsd start` and configure it to run on startup with
`rc-update add mnsavingsd`

### Upstart (for Debian/Ubuntu based distributions)

Upstart is the default init system for Debian/Ubuntu versions older than 15.04. If you are using version 15.04 or newer and haven't manually configured upstart you should follow the systemd instructions instead.

Drop mnsavingsd.conf in /etc/init.  Test by running `service mnsavingsd start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

### CentOS

Copy mnsavingsd.init to /etc/init.d/mnsavingsd. Test by running `service mnsavingsd start`.

Using this script, you can adjust the path and flags to the mnsavingsd program by
setting the MNSAVINGSD and FLAGS environment variables in the file
/etc/sysconfig/mnsavingsd. You can also use the DAEMONOPTS environment variable here.

### macOS

Copy org.mnsavings.mnsavingsd.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.mnsavings.mnsavingsd.plist`.

This Launch Agent will cause mnsavingsd to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run mnsavingsd as the current user.
You will need to modify org.mnsavings.mnsavingsd.plist if you intend to use it as a
Launch Daemon with a dedicated mnsavings user.

Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
