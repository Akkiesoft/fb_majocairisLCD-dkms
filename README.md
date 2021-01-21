# majocairisLCD-dkms

https://github.com/devemin/fbtft のマジョカアイリス細長LCDのドライバーをdkmsで管理できるようにしたものです。

## install

```
### run script
$ ./install.sh

### reboot
$ sudo reboot
```

## uninstall

```
### run script
$ ./uninstall.sh

### reboot
$ sudo reboot
```

## reference

* [devemin/fbtft](https://github.com/devemin/fbtft)
    * majocairis.dts
    * fb_majocairisLCD.c
    * fbtft.h (same as the original linux source)
* [DKMSPackaging](https://wiki.kubuntu.org/Kernel/Dev/DKMSPackaging)

## License

* GPL-2.0+
    * fbtft.h
    * fb_majocairisLCD.c
* MIT
    * all except above
