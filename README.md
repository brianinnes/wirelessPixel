# WirelessPixel software
This project contains the software to drive the wireless pixel project.  The software is targetted at a number of different devices (e.g. ATTiny 85, Raspberry Pi and Arduino) so a cross compile image is also enabled using Vagrant.

## Prequisite software to be installed on host system
The build environment has been tested on macOS Sierra (10.12), Windows 10 and Linux Mint Serena (18.1).  To create the build environment the following software needs to be installed.  Some OS software package management systems may deliver the required software, but they are often older versions, so it is recommended to follow the links and install the latest versions:
- Install [Oracle VirtualBox](https://www.virtualbox.org)
- Install [VirtualBox extension pack](http://download.virtualbox.org/virtualbox/5.1.12/Oracle_VM_VirtualBox_Extension_Pack-5.1.12-112440.vbox-extpack)
- Install [Vagrant](https://www.vagrantup.com)
- Install the plugin to allow synced folder to work.  From a command line enter :   
`vagrant plugin install vagrant-vbguest`

### Windows 10 issues   
- if getting an issue regarding user uid differences edit file `.vagrant\machines\default\virtualbox\creator_uid` and set content to `0`
- to access ssh need to install Git or Cygwin and run from the command window that has access to the ssh command, such as Git bash or cygwin terminal window.  

### Mint Linux 18.1 issues
- VirtualBox can be installed from the software manager, but Vagrant needs to be installed from the linked site otherwise the plugin will fail to install and the virtual machine will fail to build
- if getting an issue regarding user uid differences edit file `.vagrant\machines\default\virtualbox\creator_uid` and set content to your user id (default is 1000)
- Must install NFS sudo apt-get install nfs-kernel-server nfs-common portmap

## Building the cross-compile environment  
Vagrant handles the complexities of creating a virtual machine and syncing a local folder into the virtual machine.  This allows code to be edited using native OS using a preferred editor then running the compiler inside the cross-compile environment.  
To create the cross-compile environment open a command line or terminal and enter the following command:  
`vagrant up`  

This will create a new virtual machine based on Debian Jessie.  It will install updates and some additional packages then install the ARM cross-compile toolchain and then create the AVR toolchain (this will be downloaded as source and compiled).  When the cross-compile environment is initially created it may take a little time.

### Controlling the cross-compile virtual machine
The following commands must be run from the directory containing the Vagrantfile.  
The host directory containing the Vagrantfile is synced to the /vagrant directory inside the cross-compile virtual machine.
- `vagrant ssh` Will enter the virtual machine.  `exit` will return to the host command line.    
- `vagrant suspend` will sleep the virtual machine.  It can be restarted using `vagrant up`.  
- `vagrant halt` will shutdown the virtual machine.  It can be restarted using `vagrant up`.  
- `vagrant destroy` will erase the virtual machine.  It will need to be recreated with `vagrant up` which will take some time again.

When starting, stopping and destroying the cross compile virtual machine the content of the synced folder is not changed or deleted.  

## Compiling the WirelessPixel software
When the cross-compile virtual machine is initially created it will automatically compile all the software in the project.  
If you want to recompile you need to ensure the virtual machine is running (`vagrant up`) then enter the virtual machine (`vagrant ssh`).  
Once logged into the cross-compile virtual machine navigate to the synced directory (cd /vagrant)  
To compile the software enter the command `make all`
