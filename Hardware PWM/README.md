# Hardware PWM
Now that you have done the software version of PWM, it is time to start leveraging other features of these Timer Modules.

## Task
Replicate the same behavior as in the software PWM, but by using the Timer Modules ability to directly output to a GPIO Pin instead 
of managing them in software. One way to think about this is: unless there are other functions running in your code, your system should 
initialize, set the Timer Modules, and then turn off the CPU.

##MSP430FR6989
For the Hardware PWM, a button press changes the duty cycle of an LED, which changes how bright it appears. For this board, the second 
LED kept track of the duty cycle changes by turning on with every button press. After initializing the ports and enabling interrupts, 
Timer A1 was set up for debouncing in order to avoid false button readings. Timer A0 is then set up to control the PWM. 
