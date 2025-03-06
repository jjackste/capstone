#define OUTPUT_ON                                     // uncomment to turn on output for debugging

#include <Arduino.h>

long degreesToDutyCycle(int deg);

// Constants
const int cPotPin = 36;                               // GPIO pin for pot (A0)
const int cServoPin = 15;                             // GPIO pin for servo motor
const long cMinDutyCycle = 1650;                      // duty cycle for 0 degrees (adjust for motor if necessary)
const long cMaxDutyCycle = 8300;                      // duty cycle for 180 degrees (adjust for motor if necessary)

// Variables
int potVal;                                           // input value from the potentiometer
int servoPos;                                         // desired servo angle

void setup() {
#ifdef OUTPUT_ON
  Serial.begin(115200);
#endif
  pinMode(cPotPin, INPUT);                            // configure potentiometer pin for input
  ledcAttach(cServoPin, 50, 16);                      // setup servo pin for 50 Hz, 16-bit resolution
}

void loop() {
  potVal = analogRead(cPotPin);                       // read the value of the potentiometer (value between 0 and 4095)
  servoPos = map(potVal, 0, 4095, 0, 180);            // scale it into servo range 0 to 180 degrees
  ledcWrite(cServoPin, degreesToDutyCycle(servoPos)); // set the desired servo position

  doHeartbeat();                                      // update heartbeat LED
} 

// Converts servo position in degrees into the required duty cycle for an RC servo motor control signal 
// assuming 16-bit resolution (i.e., value represented as fraction of 65535). 
long degreesToDutyCycle(int deg) {
  long dutyCycle = map(deg, 0, 180, cMinDutyCycle, cMaxDutyCycle);  // convert to duty cycle
#ifdef OUTPUT_ON
  float percent = dutyCycle * 0.0015259;              // dutyCycle / 65535 * 100
  Serial.printf("Degrees %d, Duty Cycle Val: %ld = %f%%\n", servoPos, dutyCycle, percent);
#endif
  return dutyCycle;
}