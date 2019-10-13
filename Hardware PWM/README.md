# Hardware PWM
Now that you have done the software version of PWM, it is time to start leveraging other features of these Timer Modules.

## Task
Replicate the same behavior as in the software PWM, but by using the Timer Modules ability to directly output to a GPIO Pin instead 
of managing them in software. One way to think about this is: unless there are other functions running in your code, your system should 
initialize, set the Timer Modules, and then turn off the CPU.

## MSP430FR6989
For the Hardware PWM, a button press changes the duty cycle of an LED, which changes how bright it appears. For this board, the second 
LED kept track of the duty cycle changes by turning on with every button press. After initializing the ports and enabling interrupts, 
Timer A1 was set up for debouncing in order to avoid false button readings. Timer A0 is then set up to control the PWM. Then, during
the interrupt service routine, an if statement is set up to increase the PWM upon each button press. Then when it cannot get any 
brighter, the LED turns off, and the cycle restarts. It increases by 10% every button press, so it takes 10 presses to turn back off.

## MSP430G2553
The G2 board is the same as the 6989, in that the duty cycle increases with every button press. The only differences included for this 
board was that the G2 PWM started at 50% brightness before increasing to 100%, then turning off and increasing once again by increments
of 10% for each button press. 
