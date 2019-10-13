#include <msp430.h> //msp identifiers

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; //stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; //disable the GPIO power-on default high-impedance mode

    P1DIR |= BIT0; //set P1.0 to output (RED LED)
    P1SEL0 |= BIT0; //set P1.0 to use PWM
    P9DIR |= BIT7; //set P9.7 to output (GREEN LED)
    P9OUT &= ~BIT7; //Turn P9.7 off

    P1DIR &= ~BIT1; //set P1.1 to output (button)
    P1REN |= BIT1; //enable pullup resistor on button
    P1OUT |= BIT1; //enable pullup resistor on button
    P1IFG = 0x00; //clear interrupt flags
    P1IES |= BIT1; //interrupt is now set for button press
    P1IE |= BIT1; //enable interrupt

    TA1CTL |= TASSEL_2; //select SMCLK for Timer A1 setup for debouncing
    TA1CTL |= MC_2; //continuous mode
    TA1CCR0 = 0x0041; //2ms debounce time
    TA1CCTL0 |= CCIE; //set off interrupt
    TA1CTL |= TAIE; //set off timer interrupts

    TA0CTL |= TASSEL_2; //use SMCLK, Timer A0 set up for PWM
    TA0CTL |= MC_1; //up mode
    TA0CCR0 = 999; //1000 Hz PWM
    //TA0CCR1 = 499; //start at 50% duty cycle
    TA0CCTL1 |= OUTMOD_7; // resets output at CCR0, sets output at CCR1

    __bis_SR_register(LPM0_bits + GIE); //enter LPM 0 and enable interrupts

    while(1) {
            __no_operation();
        }
    } //loops infinitely

void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
{ //this one is for the debouncing
    P1IFG &= ~BIT1; //clear interrupt flag
    TA1R = 0; //reset timer
    TA1CTL &= ~MC_3; //start timer in continuous mode
    TA1CTL |= MC_2;
}

void __attribute__((interrupt(TIMER1_A0_VECTOR))) timer1_A0 (void)
{//this one is for the PWM
    TA1CTL &= ~TAIFG; //clear interrupt flag
    TA1CTL &= ~MC_3; //stop debounce timer

    //if statement for button press
    if(!(P1IN & BIT1) && (P1IES & BIT1))
    {
        P1IES &= ~BIT1; //change button interrupt edge slope so interrupt is generated on next edge
        P9OUT |= BIT7; //turn on green LED

        if(TA0CCR1 <= 900) //if the LED can still get brighter, enter this if statement
        {
            TA0CCR1 += 100; //light gets brighter (increase duty cycle)
            TA0CTL |= MC_1; //up mode
            TA0CCTL1 |= OUTMOD_7;
        }
        else
        {
            TA0CCR1 = 0; //set duty cycle back to 0
            TA0CTL &= ~MC_3; //stop timer
            TA0CCTL1 &= ~OUTMOD_7; //turn output off so it is completely off
            TA0CCTL1 &= ~OUT;
        }
    }
    //if statement for button release
    if((P1IN & BIT1) && !(P1IES & BIT1))
    {
        P1IES |= BIT1; //change button interrupt edge slope
        P9OUT &= ~BIT7; //turn off led1
    }
}
