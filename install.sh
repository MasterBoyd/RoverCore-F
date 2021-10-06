#!/bin/bash
if [[ $EUID -ne 0 ]]; then   
    echo "This script must be run as root"   
    exit 1 
fi

echo "Adding ppa:team-gcc-arm-embedded/ppa Repository to Apt-Get"
add-apt-repository ppa:team-gcc-arm-embedded/ppa
echo "Updating Apt-Get"
apt-get update
echo "Installing gcc-arm-embedded and cmake"
apt-get -y install gcc-arm-embedded cmake
echo "Moving to Build Folder"
cd Build
echo "Git clone Cgreen"
git clone https://github.com/cgreen-devs/cgreen.git
echo "Running Cgreen Makefile"
make -C cgreen
echo "Testing Built Cgreen."
make test -C cgreen
echo "Installing Cgreen into the system."
make install -C cgreen
ldconfig -v
# cp $(pwd)/include/cgreen/cgreen_value.h /usr/local/include/cgreen