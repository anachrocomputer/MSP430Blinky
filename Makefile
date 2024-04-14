# Makefile for the MSP430G2231 blinky

CC=msp430-gcc
LD=msp430-gcc

MCU=msp430g2231

COMMON=-mmcu=$(MCU)

CFLAGS=$(COMMON) -Wall -Os -c
LDFLAGS=$(COMMON) -Wl,-Map=blinky.map,--relax

all: blinky.elf
.PHONY: all

blinky.o: blinky.c
	$(CC) $(CFLAGS) -o $@ $^

blinky.elf: blinky.o
	$(LD) $(LDFLAGS) -o $@ $^

prog: blinky.elf
	mspdebug rf2500 'prog blinky.elf'
.PHONY: prog

clean:
	-rm -f blinky.o blinky.elf blinky.hex blinky.map
.PHONY: clean

