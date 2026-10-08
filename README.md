# Introduction
This repository is meant to be an extention of support for MIFARE DESFire EV2 &amp; EV3 standars in open-source library libfreefare.
All the work is considered to be a part of my Bachelor thesis.

# Installation

## For UNIX systems

You can use released version (see **Download** section) or development version:

First, ensure all dependencies are installed:
* [libnfc](https://github.com/nfc-tools/libnfc);
* git;
* Autotools (autoconf, automake, libtool);
* OpenSSL development package.
```
apt-get install autoconf automake git libtool libssl-dev pkg-config
```

Clone this repository:
```
git clone https://github.com/nfc-tools/libfreefare.git
cd libfreefare
```

Before compiling, remember to run:
```
autoreconf -vis
```

You can now compile **libfreefare** the usual autotools way:
```
./configure --prefix=/usr
make
sudo make install
```
