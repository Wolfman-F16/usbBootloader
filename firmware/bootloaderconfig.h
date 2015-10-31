/*
  bootloaderconfig.h - part of AVRUSBBoot firmware

  Thomas Fischl <tfischl@gmx.de>

  License:
  The project is built with AVR USB driver by Objective Development, which is
  published under a proprietary Open Source license. To conform with this
  license, USBasp is distributed under the same license conditions. See
  documentation.

  Creation Date..: 2006-03-18
  Last change....: 2006-06-25

  To adapt the bootloader to your hardware, you have to modify the following files:
  - bootloaderconfig.h (this file):
    Define the condition when the bootloader should be started and the initialisation of the
    hardware
  - usbconfig.h:
    Define the used data line pins. You have to adapt USB_CFG_IOPORT, USB_CFG_DMINUS_BIT and 
    USB_CFG_DPLUS_BIT to your hardware. The rest should be left unchanged.
*/

#ifndef __bootloaderconfig_h_included__
#define __bootloaderconfig_h_included__

#include "usbconfig.h"

/*
 * set common wire 13 to low: ADF select activates bootloader.
 * PD7 is status LED.
 */
#define BOOTLOADER_INIT \
    PORTA = 0x00;  /* enable multiplexer */                                 \
    DDRA  = 0x80;                                                           \
    PORTB = 0x0D;  /* set multiplexer for channel 13 */                     \
    DDRB  = 0x0F;                                                           \
    PORTC = 0x01;  /* PC0 is pulled low if ADF selected */                  \
    DDRC  = 0x00;                                                           \
    PORTD = (1 << USB_CFG_DMINUS_BIT | 1 << USB_CFG_DPLUS_BIT | 0 << PD7);  \
    DDRD  = (1 << USB_CFG_DMINUS_BIT | 1 << USB_CFG_DPLUS_BIT | 1 << PD7);

/*
 * on deprecated SimUsbKey hardware, this is the middle pin on the outer SPI
 * connector row
 */
#define BOOTLOADER_CONDITION ((PINC & (1 << PC0)) == 0)

#endif /* __bootloader_h_included__ */
