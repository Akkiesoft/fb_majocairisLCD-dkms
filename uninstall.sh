#!/bin/bash

### uninstall drive and dkms
sudo dkms remove fb_majocairisLCD/0.1 --all
sudo apt remove dkms

### uninstall device tree
sudo rm /boot/overlays/majocairis.dtbo
sudo sed -i '/^dtoverlay=majocairis$/d' /boot/config.txt

### remove source codes
rm -rf /usr/src/fb_majocairisLCD-dkms
