// https://github.com/afeld/arduino_low_battery

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

void turnOnLed() {
  digitalWrite(ledPin, HIGH);
}

void blinkOnce() {
  turnOnLed();
  timer.setTimeout(50, turnOffLed);
}

void startBlinking() {
  intervalId = timer.setInterval(blinkInterval, blinkOnce);
}

void stopBlinking() {
  timer.deleteTimer(intervalId);
  intervalId = -1;
  turnOffLed();
}

void setup() {
  pinMode(ledPin, OUTPUT);
  turnOffLed();
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
