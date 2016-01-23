/*
  Aruduino low batter indicator

  Blinks once every specified number of milliseconds when the battery is low.

  Based on:
  http://www.instructables.com/id/Arduino-Battery-Voltage-Indicator/?ALLSTEPS

  Depends on:
  http://playground.arduino.cc/Code/SimpleTimer

  * Resistors are aligned in series.
  * One end goes to Battery - and also to Arduino GND
  * The other goes to Battery + and also to Arduino Vin
  * The middle (connection between two resistors) goes to Arduino A0

  Diagram:
  http://cdn.instructables.com/FZG/1JIS/I9EORGUE/FZG1JISI9EORGUE.LARGE.jpg
*/

#include <SimpleTimer.h>

// the timer object
SimpleTimer timer;

const int sensorPin = A0;
const int ledPin = 13;
const float voltageThreshold = 6.00;
const int blinkInterval = 1000 * 4; // amount of time between blinks, in ms

int intervalId = -1;

float getVoltage() {
  int sensorValue = analogRead(sensorPin); // read the A0 pin value
  return sensorValue * (5.00 / 1023.00) * 2; // convert the value to a true voltage
}

void turnOffLed() {
  digitalWrite(ledPin, LOW);
}

void blinkOnce() {
  digitalWrite(ledPin, HIGH);
  timer.setTimeout(50, turnOffLed);
}

void startBlinking() {
  intervalId = timer.setInterval(blinkInterval, blinkOnce);
}

void stopBlinking() {
  timer.deleteTimer(intervalId);
  intervalId = -1;
  // make sure LED is off
  digitalWrite(ledPin, LOW);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  checkVoltage();
  timer.run();
}

void checkVoltage() {
  float voltage = getVoltage();
  if (voltage < voltageThreshold) {
    // check if already blinking
    if (intervalId < 0) {
      startBlinking();
    }
  } else {
    // check if already blinking
    if (intervalId >= 0) {
      stopBlinking();
    }
  }
}
