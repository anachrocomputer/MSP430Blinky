# MSP430Blinky #

A simple MSP430 test program to verify toolchain, programmer and chip.
The hardware is the MSP430 LaunchPad with the MSP430G2231 fitted.

The programs are in C and may be compiled with GCC on Linux.

## Building and Programming ##

First of all, we'll need the MSP430 cross-compiler:

`sudo apt install gcc-msp430`

To program the chip, we need 'mspdebug':

`sudo apt install mspdebug`

Finally, to compile and link the code:

`make`

Additional Makefile targets are used to program the chip:

`make prog`

The LED on P1.0 (red) should blink.

