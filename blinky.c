/* blinky --- blink an LED on the MSP430G2231               2024-04-14 */

#include <msp430.h>

int main(void)
{
   WDTCTL = WDTHOLD | WDTPW;    // Disable the watchdog timer
   
   P1DIR = BIT0;                // Enable LED pin as output
   
   while (1) {
      volatile int dally;
         
      P1OUT = BIT0;             // LED ON
      
      for (dally = 0; dally < 30000; dally++)
         ;
         
      P1OUT = 0;                // LED OFF
      
      for (dally = 0; dally < 30000; dally++)
         ;
   }
}

