#!/bin/bash

### install dkms
sudo apt update
sudo apt install -y dkms

### install driver
sudo cp -a fb_majocairisLCD-0.1 /usr/src/
sudo dkms install fb_majocairisLCD/0.1

### install device tree file and config
sudo cp dtoverlay/majocairis.dtbo /boot/overlays/majocairis.dtbo

grep "^dtoverlay=majocairis" /boot/config.txt
if [ $? -eq 1 ] ; then
  echo 'dtoverlay=majocairis' | sudo tee -a /boot/config.txt
fi

echo "Installation is complete."
