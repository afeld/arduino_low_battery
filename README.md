# Arduino low battery indicator

Blinks once every specified number of milliseconds when the battery is low. Based on [this Instructable](http://www.instructables.com/id/Arduino-Battery-Voltage-Indicator/?ALLSTEPS).

## Setup

Depends on [`SimpleTimer`](http://playground.arduino.cc/Code/SimpleTimer).

* Resistors are aligned in series.
* One end goes to Battery - and also to Arduino GND
* The other goes to Battery + and also to Arduino Vin
* The middle (connection between two resistors) goes to Arduino A0

![diagram](http://cdn.instructables.com/FZG/1JIS/I9EORGUE/FZG1JISI9EORGUE.LARGE.jpg)
