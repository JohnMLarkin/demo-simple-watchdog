# Simple Demonstration of Watchdog

This program demonstrates the use of Mbed's Watchdog class.

When the program first starts it:
* prints "It is a good day to be alive"
* starts the watchdog with a timeout value of 7 s
* sets an LED counter to display 7 (in binary)
* sets a Ticker to decrease the count by 1 each second

In the program's superloop:
* a heartbeat LED is toggled
* pin 5 is monitored and as long as it is not HIGH then the loop continues
* sleep for 250 ms
* call the `all_is_well` function that 
  * resets the watchdog timer via its `kick` method
  * resets the LED counter to 7

The flow of the superloop is interrupted if pin 5 is HIGH when it is checked:
* it prints "Ouch!"
* it turns the heartbeat off
* it then enters an endless loop so even if pin 5 goes LOW again it never makes it to `all_is_well` again

Except the watchdog comes to the rescue! If it has not had a `kick` for 7 seconds, it resets the microcontroller and the program restarts.