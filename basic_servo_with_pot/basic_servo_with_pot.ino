#include <Arduino.h>
#include <Servo.h>

long degreesToDutyCycle(int deg);

// Constants
const int cPotPin = A0;                               // GPIO pin for pot
const int cServoPin = 15;                             // GPIO pin for servo motor

// Variables
int potVal;                                           // input value from the potentiometer
int servoPos;                                         // desired servo angle

void setup() {
  Serial.begin(9600);
  myServo.attach(cServoPin);                                  // setup servo pin for 50 Hz, 16-bit resolution
}

void loop() {
  potVal = analogRead(cPotPin);                       // read the value of the potentiometer (value between 0 and 4095)
  servoPos = map(potVal, 0, 1023, 0, 180);            // scale it into servo range 0 to 180 degrees
  myServo.write(servoPos); // set the desired servo position

  Serial.printf("Pot Value: %d\n", potVal);
  Serial.printf("Servo Angle: %d\n", servoPos);
} 
