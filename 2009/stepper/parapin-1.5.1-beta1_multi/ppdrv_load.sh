#!/bin/sh

# Loading script for parapindriver, should be run late in the boot process
# as root.  Kicking it off from the end of /etc/rc.local is usually fine.
# You must have parport.o, kparapin.o and parapindriver.o in a location
# that insmod can find them.

# The device name we want to use.  This can be whatever you choose.
DEVNAME="ppdrv"

# Be sure a depmod has been run, so the symbols in kparapin and
# parapindriver can be seen
depmod

# Make sure the requisite modules are loaded first.  Uncomment either
# of these that are not already being loaded in your configuration.
rmmod lp
rmmod parapindriver
rmmod kparapin
rmmod parport_pc
rmmod ppdev
rmmod parport
modprobe parport
modprobe parport_pc
modprobe kparapin

# Load parapindriver, passing in the device name
modprobe parapindriver 

# Make our device node, using the dynamic major that was assigned to
# parapin driver when it registered itself.

rm -f /dev/${DEVNAME}
rm -f /dev/${DEVNAME}0
rm -f /dev/${DEVNAME}1

mknod /dev/${DEVNAME} u `grep $DEVNAME /proc/devices | cut -d " " -f 1` 0
mknod /dev/${DEVNAME}0 u `grep $DEVNAME /proc/devices | cut -d " " -f 1` 0
mknod /dev/${DEVNAME}1 u `grep $DEVNAME /proc/devices | cut -d " " -f 1` 1

# Change mode and ownership here if necessary
chmod 777 /dev/${DEVNAME}
chown root /dev/${DEVNAME}
chgrp root /dev/${DEVNAME}

chmod 777 /dev/${DEVNAME}0
chown root /dev/${DEVNAME}0
chgrp root /dev/${DEVNAME}0

chmod 777 /dev/${DEVNAME}1
chown root /dev/${DEVNAME}1
chgrp root /dev/${DEVNAME}1
