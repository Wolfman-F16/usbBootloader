# Name: Makefile
# Project: AVRUSBBoot
# Modified by: Thomas Fischl
# Modified: 2006-06-25

# Original file by: Christian Starkjohann
# Creation Date: 2004-12-29
# Tabsize: 4
# Copyright: (c) 2005 by OBJECTIVE DEVELOPMENT Software GmbH
# License: Proprietary, free under certain conditions. See Documentation.
# This Revision: $Id: Makefile 147 2006-03-01 17:33:03Z cs $
# atmega 8
# hfuse=0xd8 #bootloader active
# hfuse=0xd9 #bootloader inactive
# atmega16
# hfuse=D8 

BOOTLOADER_ADDRESS = 0x3800 # = (0x1c00 << 1)
speed = 16000000
mcu = atmega16
avrmcu = m16

LDFLAGS += -Wl,--section-start=.text=$(BOOTLOADER_ADDRESS)

SERIAL = 'echo /dev/ttyS5'
UISP = avrdude -c stk500v2 -P $(SERIAL) -p $(avrmcu)
# The two lines above are for "uisp" and the AVR910 serial programmer connected
# to a Keyspan USB to serial converter to a Mac running Mac OS X.
# Choose your favorite programmer and interface.

COMPILE = avr-gcc -Wall -Os -Iusbdrv -I. -mmcu=$(mcu) -DF_CPU=$(speed) 
#-DDEBUG_LEVEL=2
# NEVER compile the final product with debugging! Any debug output will
# distort timing so that the specs can't be met.

OBJECTS = usbdrv/usbdrv.o usbdrv/usbdrvasm.o usbdrv/oddebug.o main.o
# Note that we link usbdrv.o first! This is required for correct alignment of
# driver-internal global variables!


# symbolic targets:
all:	main.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(UISP) -U flash:w:../Release/main.hex -U hfuse:v:0xD0:m

avrdude: 
	avrdude -c stk500v2 -p atmega16 -U flash:w:main.hex

# Fuse low byte:
# 0xef = 1 1 1 0   1 1 1 1
#        ^ ^ \+/   \--+--/
#        | |  |       +------- CKSEL 3..0 (clock selection -> crystal @ 12 MHz)
#        | |  +--------------- SUT 1..0 (BOD enabled, fast rising power)
#        | +------------------ CKOUT (clock output on CKOUT pin -> disabled)
#        +-------------------- CKDIV8 (divide clock by 8 -> don't divide)
#
# Fuse high byte:
# 0xdb = 1 1 0 1   1 0 1 1
#        ^ ^ ^ ^   \-+-/ ^
#        | | | |     |   +---- RSTDISBL (disable external reset -> enabled)
#        | | | |     +-------- BODLEVEL 2..0 (brownout trigger level -> 2.7V)
#        | | | +-------------- WDTON (watchdog timer always on -> disable)
#        | | +---------------- SPIEN (enable serial programming -> enabled)
#        | +------------------ EESAVE (preserve EEPROM on Chip Erase -> not preserved)
#        +-------------------- DWEN (debug wire enable)
fuse_tiny2313:	# only needed for attiny2313
	$(UISP) --wr_fuse_l=0xef --wr_fuse_h=0xdb


clean:
	rm -f ../Release/main.hex main.lst main.obj main.cof main.list main.map main.eep.hex main.bin *.o usbdrv/*.o main.s usbdrv/oddebug.s usbdrv/usbdrv.s

# file targets:
main.bin:	$(OBJECTS)
	$(COMPILE) -o ../Release/main.bin $(OBJECTS) $(LDFLAGS) -Wl,-Map,../Release/main.map

main.hex:	main.bin
	rm -f main.hex main.eep.hex
	avr-objcopy -j .text -j .data -O ihex ../Release/main.bin ../Release/main.hex
	./checksize ../Release/main.bin
# do the checksize script as our last action to allow successful compilation
# on Windows with WinAVR where the Unix commands will fail.

disasm:	main.bin
	avr-objdump -d ../Release/main.bin

cpp:
	$(COMPILE) -E main.c
