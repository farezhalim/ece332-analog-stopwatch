# ECE332 Analog Stopwatch

## Description
The purpose of the Analog Stopwatch is to track the time passed after the press of a button. A piezo buzzer generates a 1kHz tone for 300ms at the 
start of each minute passed after the press of the button. The Analog Stopwatch has an error of ±1s/minute. 

## Operating Conditions
Operating voltage range of the device: 5V to 5.5V
Operating temperature: +20ºC to +80ºC
Storage temperature: -65ºC to +150ºC
Maximum DC Current per I/O pin: 30.0mA 

## Setup Instructions
To operate the device, connect VCC (Pin 7) to a voltage source that is within the operating voltage range, GND (Pin 8, 22) to ground. 
The motor driver should also be connected to a 12V supply. Refer to Figure 1 for the device’s schematic. 

## Usage Instructions
Wind the hand to “12” for its starting position. Then, press the button to start the stopwatch. A subsequent press will stop the
hand from ticking while it is running. An additional press while the stopwatch is paused will resume counting and reset the next buzzer 
event to one minute from the time it was pressed.

## Testing
### Tentative Goals:
* Track/display time elapsed through an analog representation after power is applied with an error of +/- 10s/hour.
* ‘Seconds’ hand will be controlled by a stepper motor in a clockwise direction.
* Stop/start the analog timer through the press of a button.
* Reset/set analog clock by hand.
* Notify user of each minute elapsed through a 1kHz tone that occurs for 300ms at the start of each full minute passed.
### Achieved Goals:
* Track/display time elapsed through an analog representation after power is applied with an error of +/- 1s/minute.
* ‘Seconds’ hand is controlled by a stepper motor in a clockwise direction.
* Stop/start the analog timer through the press of a button.
* Reset/set analog clock by hand.
* Notifies user of each minute elapsed through a 1kHz tone that occurs for 300ms at the start of each full minute passed.

The above achieved goals were verified through observation and testing in comparison to an accurate timer, however, compromises 
were met in order to meet these intended specifications. The stepper motor used was specified at 1.8 degrees per step, totaling 
to 200 steps per revolution. The number of seconds in a minute does not evenly fit into this total and therefore results in the 
analog stopwatch achieving accuracy and precision to the minute, within the specified error, but not to the second. A single step 
of the second hand equates to 0.3 seconds. Though the analog clock is able to be started and stopped through the press of a button, 
the first start of the ‘seconds’ hand after power is connected is delayed due to the time required to establish initial current flow 
in the motor.
