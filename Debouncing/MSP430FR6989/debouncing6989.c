#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; //stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; //disable the GPIO power-on default high-impedance mode

    P1DIR |= BIT0; //LED output P1.0
    P1OUT &= ~BIT0;

    P1DIR &= ~BIT1; //button input
    P1REN |= BIT1;
    P1OUT |= BIT1;
    P1IFG = 0x00; //clear interrupt flags
    P1IES |= BIT1; //button press triggers interrupts
    P1IE |= BIT1;

    TA0CTL |= TASSEL_2; //SMCLK
    TA0CTL |= MC_2; //continuous mode
    TA0CCR0 = 0x0041; //count up to 2ms
    TA0CCTL0 |= CCIE;
    TA0CTL |= TAIE; //interrupts

    __bis_SR_register(LPM0_bits + GIE); //LPM0

    while(1) {
              __no_operation();
          }
    //loops infinitely
}

void __attribute__((interrupt(TIMER0_A0_VECTOR))) Timer_A0 (void)
{//ISR
    TA0CTL &= ~TAIFG;
    TA0CTL &= ~MC_3; //timer stop

    if(!(P1IN & BIT1))
        P1OUT ^= BIT0;
}

void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
{//button interrupt
    P1IFG &= ~BIT1;

    TA0R = 0; //timer RST
    TA0CTL &= ~MC_3;
    TA0CTL |= MC_2;
}
