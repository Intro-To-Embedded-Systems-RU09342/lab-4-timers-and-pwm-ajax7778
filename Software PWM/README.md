# Software PWM
Most microprocessors will have a Timer module, but depending on the device, some may not come with pre-built PWM modules. 
Instead, you may have to use software techniques to synthesize PWM on your own.

## Task
Generate a 1kHz PWM signal with a duty cycle between 0% and 100%. Upon processor start up, PWM one of the on-board LEDs at a 50% duty 
cycle. Upon pressing one of the on-board buttons, the duty cycle of the LED should increase by 10%. Once you have reached 100%, the 
duty cycle should go back to 0% on the next button press. You'll also need to implement the other LED to light up when the Duty Cycle 
button is depressed and turns back off when it is let go. This is to help you figure out if the button has triggered multiple interrupts.

## MSP430FR6989
I actually read and did the Hardware PWM first, before realizing that the software version was supposed to be done first. However, there
are not many differences besides a few. Both utilize debouncing for this board and start the LED at a 50% duty cycle. The LED becomes
brighter and brighter with each button press until it reaches 100% brightness and turns off. Then the cycle starts again, increasing by 
10%. The second LED, in this case P9.7, blinks with every press of button P1.1, to track how many times the button is pressed. With the
use of debouncing, there are less chances of the duty cycle reading wrong or reading a button press that did not happen.

## MSP430G2553
The hardware code for the G2 was written slightly differently than the software code. It was written in such a way that the debouncing
function would not work, but for the way the software version of the code was written, the debouncing worked. Otherwise, the codes for 
the G2 and the 6989 are pretty much exactly the same, both starting at 50% duty cycle and increasing with each button press. Timers are
utilized as well as interrupts. 
