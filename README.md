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

## For Linux systems

First, ensure all dependencies are installed:
* [libnfc](https://github.com/nfc-tools/libnfc);
* git;
* OpenSSL development package.
```
sudo apt update
sudo apt install build-essential pkg-config libnfc-dev libssl-dev libnfc-bin git
```

----------------------------------------------------------------------
### Additional seup for WSL (skip down if not needed)
Open PowerShell (as Administrator) in Windows and type:
```
winget install --interactive --exact dorssel.usbipd-win
```

Successful installation can be verified using:
```
usbipd --version
```

Start your WSL and insert:
```
sudo apt update && sudo apt install usbutils hwdata -y
```

Back in the PowerShell use following command:
```
usbipd list
```
Locate the nfc reader and note its **BUSID**

Now in the same PowerShell, type:
```
usbipd bind --busid <BUSID>
usbipd attach --wsl --busid <BUSID> --auto-attach
```
----------------------------------------------------------------------

Verify which serial port is your device using for the **NFC reader**:
```
ls /dev/ttyUSB* /dev/ttyACM* 2>/dev/null
```
>Now let's assume that the correct port is *dev/ttyUSB0*

Modify the configuration file **/etc/nfc/libnfc.conf**.
Recomended configuration:
```
allow_autoscan = true
allow_intrusive_scan = false

device.name = "nfc.usb.raeder"
device.connstring = "pn532_uart:/dev/ttyUSB0:115200"
```
>Please note that after the port, there is also number after the port.
>This number is a baud rate. it assures the correct data transmission speed in bits per second between USB serial adapter and the nfc chip.

Now, following command should be able to perform successfully:
```
sudo nfc-poll
```

Finally, You are now ready to compile **libfreefare** the usual Makefile way from the root directory:
```
make clean && make
```
