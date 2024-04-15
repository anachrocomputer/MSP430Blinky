/* blinky --- blink an LED on the MSP430G2231               2024-04-14 */

#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

volatile uint32_t MilliSeconds = 0UL;
volatile bool Tick = false;

#pragma vector = TIMER0_A0_VECTOR
__interrupt void MilliSecondTimerISR(void)
{
   MilliSeconds++;
   Tick = true;
   
   P1OUT ^= BIT4;     // Toggle P1.4 (500Hz)
}


/* millis --- Arduino-like function to return milliseconds since start-up */

uint32_t millis(void)
{
   __dint();      // Disable interrupts around access to non-atomic object
   const uint32_t ms = MilliSeconds;
   __eint();
   
   return (ms);
}


int main(void)
{
   uint32_t end;

   WDTCTL = WDTHOLD | WDTPW;    // Disable the watchdog timer
   
   P1DIR = BIT0 | BIT4;         // Enable LED pin and SQWAVE pin as outputs
   
   BCSCTL1 = CALBC1_1MHZ;       // Set MCLK = SMCLK = 1MHz
   DCOCTL = CALDCO_1MHZ;
	
   TACCR0 = 0;        // Disable timer A initially
   TACCTL0 |= CCIE;   // Enable interrupt for CCR0.
   TACTL = TASSEL_2 | ID_0 | MC_1; // SMCLK source, divide by 1, count up to TACCR0
   TAR = 0;           // Zero the counter
   TACCR0 = 1000 - 1; // Start Timer for 1kHz/1ms interrupt
   
   __eint();      // Enable global interrupts
   
   end = millis() + 500UL;
   
   while (1) {
      if (Tick) {
         if (millis() >= end) {
            end = millis() + 500UL;
            P1OUT ^= BIT0;            // Toggle LED pin
         }
         
         // Nudge watchdog here
         
         Tick = false;
      }
      
      // CPU is idle in this part of the loop
   }
}

