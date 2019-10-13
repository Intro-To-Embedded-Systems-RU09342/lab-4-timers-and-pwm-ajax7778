#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; //stop watchdog timer

    P1DIR |= BIT0; //LED to output, P1.0
    P1OUT &= ~BIT0;
    P1DIR |= BIT6; //LED to output, P1.6
    P1OUT &= ~BIT6;

    P1DIR &= ~BIT3; //BUTTON to input, P1.3
    P1IFG = 0x00;
    P1IES |= BIT3; //button press triggers interrupts
    P1IE |= BIT3;

    //debounce timer
    TA0CTL |= TASSEL_2; //SMCLK
    TA0CTL |= MC_2; //continuous mode
    TA0CCR0 = 0x0041; //counts up to 2ms
    TA0CCTL0 |= CCIE;
    TA0CTL |= TAIE; //interrupts

    //PWM timer
    TA1CTL |= TASSEL_2; //SMCLK
    TA1CTL |= MC_1; //up mode
    TA1CCR0 = 999; //1000 Hz (highest value for PWM)
    TA1CCR1 = 499; //allows LED to start at 50% brightness
    TA1CCTL0 |= CCIE;
    TA1CCTL1 |= CCIE;
    TA1CTL |= TAIE; //interrupts

    __bis_SR_register(LPM0_bits + GIE); //LPM0

    while(1) {
            __no_operation();
        }
}

void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
{ //debounce
    P1IFG &= ~BIT3;
    TA0R = 0; //reset timer
    TA0CTL &= ~MC_3; //start timer in continuous mode
    TA0CTL |= MC_2;
}

void __attribute__((interrupt(TIMER0_A0_VECTOR))) timer0_A0 (void)
{//PWM
    TA0CTL &= ~TAIFG; //clear interrupt flag
    TA0CTL &= ~MC_3; //stop debounce timer

    //if statement for button press
    if(!(P1IN & BIT3) && (P1IES & BIT3))
    {
        P1IES &= ~BIT3; //button interrupt
        P1OUT |= BIT6; //turn on LED

        if(TA1CCR1 <= 900) //if duty cycle can be increased, increase it by 10%
        {
            TA1CCR1 += 100;
            TA1CTL |= MC_1;
        }
        else //if it can't be increased, turn off LED and stop timer.
        {
            TA1CCR1 = 0;
            P1OUT &= ~BIT0;
            TA1CTL &= ~MC_3;
        }
    }

    //if statement for button release
    if((P1IN & BIT3) && !(P1IES & BIT3))
    {
        P1IES |= BIT3;
        P1OUT &= ~BIT6; //turn off tracking LED
    }
}

void __attribute__((interrupt(TIMER1_A0_VECTOR))) timer1_A0 (void)
{//ISR timer 1 A0
    TA1CTL &= ~TAIFG; //clear interrupt flag
    P1OUT |= BIT0; //turn on led0
}

void __attribute__((interrupt(TIMER1_A1_VECTOR))) timer1_A1 (void)
{//ISR timer 1 A1
    if(TA1IV == 0x02) //if interrupt was generated from CCR1 compare
        P1OUT &= ~BIT0; //turn off led0
}
