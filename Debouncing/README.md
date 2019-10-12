# Software Debouncing
Debouncing a signal is a necessary step when adding mechanical switches to digital circuits so a single press doesn't appear like multiple 
presses. You're going to need this feature in a later portion of this lab as you'll be using a button press to change the duty cycle of 
your signal and you don't want to count the "false positives" as a button press. Debouncing is also only one of many applications which 
would require the use of built in Timers to allow for other processes to take place. Check out this nice tutorial on the subject. 
[http://www.labbookpages.co.uk/electronics/debounce.html]

## Task
You'll need to use the TIMER modules within the MSP430 processors to implement a debounced switch to control the state of an LED. 
You'll likely want to hook up your buttons on the development boards to an oscilloscope to see how much time it takes for the buttons 
to settle. The idea here is that your processor should be able to run other code, while relying on timers and interrupts to manage the 
debouncing in the background. *You should not be using polling techniques for this assignment.

## MSP430G2553
Debouncing is very important in coding because it allows for more reliable button presses. A lot of times, a button press can mess up,
and toggle multiple times or no times at all when pressed. This creates false positives and false negatives. Debouncing makes it less
likely for this to happen, and since we will be using a button to control pulse width modulation, it is important that we use 
debouncing. For the G2, a timer is initialized to count up to 2 milliseconds. When the button is pressed, it tells the timer to count to 
2 ms. Then the timer turns off and the LED turns on. When the button is released, the timer is turned back on to count up to 2 ms. 
Then, the LED turns off.
