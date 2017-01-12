# -*- mode: ruby -*-
# vi: set ft=ruby :

#**********************************************************************
# Cross-compile environment for AVR and ARM mcus
#**********************************************************************

def usbfilter_exists(vendor_id, product_id)
  #
  # Determine if a usbfilter with the provided Vendor/Product ID combination
  # already exists on this VM.
  #
  # TODO: Use a more reliable way of retrieving this information.
  #
  # NOTE: The "machinereadable" output for usbfilters is more
  #       complicated to work with (due to variable names including
  #       the numeric filter index) so we don't use it here.
  #
  machine_id_filepath = File.join(".vagrant","machines","default","virtualbox","id")

  if not File.exists? machine_id_filepath
    # VM hasn't been created yet.
    return false
  end

  vm_info = `VBoxManage showvminfo $(<#{machine_id_filepath})`
  filter_match = "VendorId:         #{vendor_id}\nProductId:        #{product_id}\n"
  return vm_info.include? filter_match
end

def better_usbfilter_add(vb, vendor_id, product_id, filter_name)
  #
  # This is a workaround for the fact VirtualBox doesn't provide
  # a way for preventing duplicate USB filters from being added.
  #
  # TODO: Implement this in a way that it doesn't get run multiple
  #       times on each Vagrantfile parsing.
  #
  if not usbfilter_exists(vendor_id, product_id)
    vb.customize ["usbfilter", "add", "0",
                  "--target", :id,
                  "--name", filter_name,
                  "--vendorid", vendor_id,
                  "--productid", product_id
                  ]
  end
end
Vagrant.configure("2") do |config|
  config.vbguest.auto_update = true
  config.vm.network "public_network"
  config.vm.network "private_network", ip: "192.168.50.50"
  config.vm.provider "virtualbox" do |v|
    v.memory = 1024
    v.cpus = 2
    v.customize [
        "storagectl", :id,
        "--name", "SATA Controller",
        "--hostiocache", "on"
    ]
    better_usbfilter_add(v, "1a86", "7523", "Arduino Nano")
    better_usbfilter_add(v, "03eb", "2104", "AAVRISP mkII")
    better_usbfilter_add(v, "0403", "6001", "FTDI TTL232R 3V3")
    better_usbfilter_add(v, "2a03", "0043", "Arduino UNO")
    better_usbfilter_add(v, "16c0", "05dc", "USBasp")
    v.customize ["modifyvm", :id, "--usb", "on"]
    v.customize ["modifyvm", :id, "--usbxhci", "on"]
  end
  config.vm.box = "debian/jessie64"
#--------
# If larger filesystem is needed use the image in the commented out line below
# rather than the debian/jessie64 image
#--------
#  config.vm.box = "wholebits/debian8-64" # Linux ebian-8-64 3.16.0-4-amd64 #1 SMP Debian 3.16.36-1+deb8u2 (2016-10-19) x86_64 GNU/Linux
  config.vm.synced_folder ".", "/vagrant", type: "virtualbox", nfs: true

  config.vm.provision "shell", inline: <<-SHELL
    echo "********** Updating and extending base **********"
    apt-get update
    apt-get upgrade -y
    apt-get install -y build-essential curl python-pip python-dev unzip git usbutils
    apt-get install -y libusb-1.0 libusb-dev libelf-dev libftdi-dev
    apt-get install -y avahi-daemon avahi-discover avahi-dnsconfd avahi-utils libnss-mdns
    echo "********** Installing ARM 7 build tools **********"
    echo "deb http://emdebian.org/tools/debian/ jessie main" >> /etc/apt/sources.list.d/crosstools.list
    curl http://emdebian.org/tools/debian/emdebian-toolchain-archive.key | sudo apt-key add -
    dpkg --add-architecture armhf
    apt-get update
    apt-get install -y crossbuild-essential-armhf
    echo "********** Installing ARM 6 build tools **********"
    dpkg --add-architecture i386
    apt-get update
    apt-get install -y libstdc++6:i386 libgcc1:i386 zlib1g:i386
    git clone https://github.com/raspberrypi/tools.git /opt/arm-bcm2708hardfp-linux-gnueabi
    echo "********** Installing AVR build tools **********"
    apt-get install -y gcc-avr binutils-avr avr-libc gdb-avr avrdude
#
#   Create the udev rules to ensure devices have a know name for make rules
#   and ensure correct permissions are set to allow vagrant user to access the devices
#
    usermod -a -G dialout vagrant
    cat > /etc/udev/avrisp.rules <<- "EOF"
SUBSYSTEM!="usb", ACTION!="add", GOTO="avrisp_end"
# Atmel Corp. JTAG ICE mkII
ATTR{idVendor}=="03eb", ATTR{idProduct}=="2103", MODE="660", GROUP="dialout"
# Atmel Corp. AVRISP mkII
ATTR{idVendor}=="03eb", ATTR{idProduct}=="2104", MODE="660", GROUP="dialout"
# Atmel Corp. Dragon
ATTR{idVendor}=="03eb", ATTR{idProduct}=="2107", MODE="660", GROUP="dialout"
# USBasp
ATTR{idVendor}=="16c0", ATTR{idProduct}=="05dc", MODE="660", GROUP="dialout"


LABEL="avrisp_end"
EOF
    cat > /etc/udev/links.rules <<- "EOF"
SUBSYSTEM!="usb", ACTION!="add", GOTO="links_end"
# QinHeng Electronics CH340 nano
SUBSYSTEM=="tty", SUBSYSTEMS=="usb", DRIVERS=="usb", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="7523", MODE="660", SYMLINK+="ttyUSBnano"
# FTDI 3v3 tty cable
SUBSYSTEM=="tty", SUBSYSTEMS=="usb", DRIVERS=="usb", ATTRS{idVendor}=="0403", ATTRS{idProduct}=="6001", MODE="660", SYMLINK+="ttyUSBftdi"
# Arduino UNO
SUBSYSTEM=="tty", SUBSYSTEMS=="usb", DRIVERS=="usb", ATTRS{idVendor}=="2a03", ATTRS{idProduct}=="0043", MODE="660", SYMLINK+="ttyUSBuno"

LABEL="links_end"
EOF
cd /etc/udev/rules.d
ln ../avrisp.rules 10-avrisp.rules
ln ../links.rules 10-links.rules
systemctl restart udev
udevadm control --reload-rules; udevadm trigger
# Build AVR toolchain from source - not needed as use Debian packages
#    apt-get install -y automake texinfo autoconf
#    apt-get install -y texlive-latex-base texlive-font-utils texlive-latex-recommended
#    apt-get install -y texlive-latex-extra bison expat netpbm doxygen flex transfig
#    mkdir /opt/avr/
#    cd /opt/avr
#    curl -L -O http://distribute.atmel.no/tools/opensource/Atmel-AVR-GNU-Toolchain/3.5.4/avr-binutils.tar.bz2
#    curl -L -O http://distribute.atmel.no/tools/opensource/Atmel-AVR-GNU-Toolchain/3.5.4/avr-gcc.tar.bz2
#    curl -L -O http://distribute.atmel.no/tools/opensource/Atmel-AVR-GNU-Toolchain/3.5.4/avr-gdb.tar.bz2
#    curl -L -O http://distribute.atmel.no/tools/opensource/Atmel-AVR-GNU-Toolchain/3.5.4/avr-libc.tar.bz2
#    curl -L -O http://distribute.atmel.no/tools/opensource/Atmel-AVR-GNU-Toolchain/3.5.4/avr8-headers.zip
#    curl -L -O http://distribute.atmel.no/tools/opensource/Atmel-AVR-GNU-Toolchain/3.5.4/build-avr8-gnu-toolchain-git.sh
#    curl -L -O http://distribute.atmel.no/tools/opensource/Atmel-AVR-GNU-Toolchain/3.5.4/SOURCES.README
#    mkdir src
#    mkdir src/headers
#    mv avr8-headers.zip src/headers
#    cd src
#    mkdir gmp
#    cd gmp
#    curl -O https://gmplib.org/download/gmp/gmp-6.1.2.tar.bz2
#    cd ..
#    mkdir mpfr
#    cd mpfr
#    curl -O http://www.mpfr.org/mpfr-current/mpfr-3.1.5.tar.gz
#    cd ..
#    mkdir mpc
#    cd mpc
#    curl -O ftp://ftp.gnu.org/gnu/mpc/mpc-1.0.2.tar.gz
#    cd ..
#    mkdir ncurses
#    cd ncurses
#    curl -O https://ftp.gnu.org/gnu/ncurses/ncurses-5.9.tar.gz
#    cd ../..
#    bzip2 -d *.bz2
#    cd src
#    tar xvf ../avr-binutils.tar
#    tar xvf ../avr-gcc.tar
#    tar xvf ../avr-gdb.tar
#    tar xvf ../avr-libc.tar
#    cd ..
#    bash build-avr8-gnu-toolchain-git.sh -s src
#    mkdir /opt/avrdude
#    cd /opt/avrdude
#    curl -L -O http://download.savannah.gnu.org/releases/avrdude/avrdude-6.3.tar.gz
#    curl -L -O http://download.savannah.gnu.org/releases/avrdude/avrdude-doc-6.3.pdf
#    tar zxvf avrdude-6.3.tar.gz
#    cd avrdude-6.3
#    ./configure
#    make
#    make install
    cd /vagrant
    make all
  SHELL
end
