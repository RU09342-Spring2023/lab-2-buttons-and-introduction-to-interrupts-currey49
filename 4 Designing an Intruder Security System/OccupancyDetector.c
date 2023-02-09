/*
* OccupancyDetector.c
*
*  Created on: Feb 9, 2023
*      Author: Matthew Currey
*/

#include <msp430.h>
#define GREENBLINK_STATE 0
#define REDBLINK_STATE 1
#define REDSOLID_STATE 2

// Put some initialization here

char state = GREENBLINK_STATE;

int main(){
    WDTCTL = WDTPW | WDTHOLD;
    P4OUT |= BIT1;
    P4DIR &= ~BIT1;
    P4REN |= BIT1;


    P2OUT |= BIT3;
    P2DIR &= ~BIT3;
    P2REN |= BIT3;


    P6OUT &= ~BIT6;
    P6DIR |= BIT6;
    P1OUT &= ~BIT0;
    P1DIR |= BIT0;

    PM5CTL0 &= ~LOCKLPM5;



    char cnt = 0;



     while(1)
        {


          switch (state) {
            case GREENBLINK_STATE:
                //DEFAULT STATE, BLINKS GREEN
            {
              cnt = 0;

             // __delay_cycles(10000);
              int x = 0;
              for(x = 0; x < 1000; x++){
                  P1OUT &= ~BIT0;
                  P6OUT ^= BIT6;// Blink the Green LED
                  x++;

                  if(!(P2IN & BIT3)){
                      state = REDBLINK_STATE;
                      break;
                  }
                  else
                  {
                    _delay_cycles(3000000);     // 3 secound delay
                  }
              }

              break;
              // If something happens, you can move into the REDBLINK_STATE
              // state = REDBLINK_STATE
            }
            case REDBLINK_STATE://IF BUTTON IS HELD IT BLINKS RED
            {



              if(!(P2IN & BIT3)){
             // IF BUTTON IS HELD
              int x = 0;
              for(x = 0; x < 1000; x++){
                  if(!(P2IN & BIT3)){ //IF BUTTON IS HELD
                  P6OUT &= ~BIT6;
                  P1OUT ^= BIT0;
                  x++;
                  _delay_cycles(3000000);     // 3 second delay

                  cnt = cnt + 1;
                  if (cnt >= 5){
                      state = REDSOLID_STATE;
                      break;
                  }
                  }
                  else
                  {
                      //IF BUTTON IS LET GO
                      state = GREENBLINK_STATE;
                      break;
                  }
              }
              }
              else
              {
                  //IF BUTTON IS LET GO
                  state = GREENBLINK_STATE;
                  break;
              }

              break;

            }
            case REDSOLID_STATE: //AFTER 10 seconds it's solid red
            {

                if (!(P4IN & BIT1)){
                    state = GREENBLINK_STATE;
                    break;
                }
               //__delay_cycles(100000);
                    P6OUT &= ~BIT6;
                    P1OUT |= BIT0;

                break;

            }
          }
      }
}
