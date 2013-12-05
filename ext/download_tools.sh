#!/bin/bash

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 
   exit 1
fi

packages="install qemu qemu-system nasm"

distro=`lsb_release -a 2> /dev/null | head -1 | cut -f 2 -d':' | tr -d "\t"`
if [ "$disto" == "Debian" -o "$disto" == "Ubuntu" ]
then
	apt-get $packages
else
	yum $packages
fi

