## Synopsis

This software is a bootloader for an ATmega16 using USB as interface. It is based on work of T. Fischl and vUSB of obdev.at.

## Motivation

The usbBootloader simplifies updates of the *UHF-Radio Control Board RP* firmware

## Installation

Installation is a single step process, covering two key points

0. loading firmware into bootloader section of ATmega16 microcontroller
0. setting ATmega16 fuse bits to activate booting to bootloader first 

```
avrdude -c usbtiny -p m16 -U flash:w:main.hex -U hfuse:v:0xD8:m
```

## Usage

The command line utility *usbBootloaderCommander* is used to interface with *usbBootloader* to upload hex files. 

## Tests

The device should show up as *AVRUSBBoot* with VID / PID : 0x16c0/0x5dc if bootloader condition is met.
The bootloader is active during power up, when the UHF Function selector is set to ADF.  

## Contributors

An issue tracker is available in case of problems.

## License

License is GPLv2
