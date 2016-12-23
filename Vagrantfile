# -*- mode: ruby -*-
# vi: set ft=ruby :
Vagrant.configure("2") do |config|
  config.vm.provider "virtualbox" do |v|
    v.memory = 1024
    v.cpus = 2
  end
  config.vm.box = "debian/jessie64"
  config.vm.synced_folder ".", "/vagrant", type: "virtualbox"

  config.vm.provision "shell", inline: <<-SHELL
    echo "********** Updating and extending base **********"
    apt-get update
    apt-get upgrade -y
    apt-get install -y build-essential curl autoconf texlive-latex-base texlive-font-utils texlive-latex-recommended
    apt-get install -y texlive-latex-extra bison expat netpbm doxygen unzip flex transfig python-pip python-dev
    apt-get install -y libusb-1.0 libusb-dev libelf-dev libftdi-devcd 
    echo "********** Installing ARM build tools **********"
    echo "deb http://emdebian.org/tools/debian/ jessie main" >> /etc/apt/sources.list.d/crosstools.list
    curl http://emdebian.org/tools/debian/emdebian-toolchain-archive.key | sudo apt-key add -
    dpkg --add-architecture armhf
    apt-get update
    apt-get install -y crossbuild-essential-armhf
    echo "********** Installing AVR build tools **********"
    mkdir /opt/avr/
    cd /opt/avr
    curl -L -O http://distribute.atmel.no/tools/opensource/Atmel-AVR-GNU-Toolchain/3.5.4/avr-binutils.tar.bz2
    curl -L -O http://distribute.atmel.no/tools/opensource/Atmel-AVR-GNU-Toolchain/3.5.4/avr-gcc.tar.bz2
    curl -L -O http://distribute.atmel.no/tools/opensource/Atmel-AVR-GNU-Toolchain/3.5.4/avr-gdb.tar.bz2
    curl -L -O http://distribute.atmel.no/tools/opensource/Atmel-AVR-GNU-Toolchain/3.5.4/avr-libc.tar.bz2
    curl -L -O http://distribute.atmel.no/tools/opensource/Atmel-AVR-GNU-Toolchain/3.5.4/avr8-headers.zip
    curl -L -O http://distribute.atmel.no/tools/opensource/Atmel-AVR-GNU-Toolchain/3.5.4/build-avr8-gnu-toolchain-git.sh
    curl -L -O http://distribute.atmel.no/tools/opensource/Atmel-AVR-GNU-Toolchain/3.5.4/SOURCES.README
    mkdir src
    mkdir src/headers
    mv avr8-headers.zip src/headers
    cd src
    mkdir gmp
    cd gmp
    curl -O https://gmplib.org/download/gmp/gmp-6.1.2.tar.bz2
    cd ..
    mkdir mpfr
    cd mpfr
    curl -O http://www.mpfr.org/mpfr-current/mpfr-3.1.5.tar.gz
    cd ..
    mkdir mpc
    cd mpc
    curl -O ftp://ftp.gnu.org/gnu/mpc/mpc-1.0.2.tar.gz
    cd ..
    mkdir ncurses
    cd ncurses
    curl -O https://ftp.gnu.org/gnu/ncurses/ncurses-5.9.tar.gz
    cd ../..
    bzip2 -d *.bz2
    cd src
    tar xvf ../avr-binutils.tar
    tar xvf ../avr-gcc.tar
    tar xvf ../avr-gdb.tar
    tar xvf ../avr-libc.tar
    cd ..
    bash build-avr8-gnu-toolchain-git.sh -s src
    mkdir /opt/avrdude
    cd /opt/avrdude
    curl -L -O http://download.savannah.gnu.org/releases/avrdude/avrdude-6.3.tar.gz
    curl -L -O http://download.savannah.gnu.org/releases/avrdude/avrdude-doc-6.3.pdf
    tar zxvf avrdude-6.3.tar.gz
    cd avrdude-6.3
    ./configure
    make
    make install
    cd /vagrant
    make all
  SHELL
end
