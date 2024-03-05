/* Code to control water pump for transwell experiment.
 * Author: Matthew Uppington
 */

// ----- Configuration parameters -----
int motorPin = 3;
int pwmPinScale = 255;
float maxPinVoltage = 5.0; // volts
float maxMotorVoltage = 4.0; // volts
float minMotorVoltage = 1.0; // volts
bool safe2run = true;
int pinValue2set = 0;

// ----- Control variable for pump speed -----
float desiredOutputRatio = 0.0; // 0 (off) - 1 (max)

void setup() {
  // Check that the pin can supply sufficient voltage.
  if (minMotorVoltage > maxPinVoltage) {
    safe2run = false;
  }
  // Check that the users desired ouput ratio is within range [0, 1].
  if (desiredOutputRatio > 1 || desiredOutputRatio < 0) {
    safe2run = false;
  }
  int pinValueUpperBound = pwmPinScale * maxMotorVoltage / maxPinVoltage;
  if (pinValueUpperBound > pwmPinScale){
    pinValueUpperBound = pwmPinScale;
  }
  int pinValueLowerBound = pwmPinScale * minMotorVoltage / maxPinVoltage;
  int pinValueRange = pinValueUpperBound - pinValueLowerBound;
  pinValue2set = pinValueLowerBound + pinValueRange * desiredOutputRatio;
  if (pinValue2set < 0) {
    pinValue2set = 0;
  }
  if (pinValue2set > pinValueUpperBound) {
    pinValue2set = pinValueUpperBound;
  }
}

void loop() {
  if (safe2run) {
    analogWrite(motorPin, pinValue2set);
  }
}
