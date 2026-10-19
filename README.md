# Introduction
This repository is meant to be an extention of support for MIFARE DESFire EV2 &amp; EV3 standars in open-source library libfreefare.
All the work is considered to be a part of my Bachelor thesis.

# Backwards compatibility with libfreefare
Files:
```
felica.c
mad.c
mifare_application.c
mifare_classic.c
mifare_ultralight.c
ntag21x_error.c
ntag21x.c
```

# Installation

## For UNIX systems

You can use released version (see **Download** section) or development version:

First, ensure all dependencies are installed:
* [libnfc](https://github.com/nfc-tools/libnfc);
* git;
* OpenSSL development package.
```
sudo apt update
sudo apt install build-essential pkg-config libnfc-dev libssl-dev libnfc-bin git
```

Edit **/etc/nfc/libnfc.conf**. Recomended configuration:
```
allow_autoscan = true
allow_intrusive_scan = false

device.name = "nfc.usb.raeder"
device.connstring = "pn532_uart:/dev/ttyUSB0:115200"
```

You can now compile **libfreefare** the usual Makefile way:
```
make clean
make
```


