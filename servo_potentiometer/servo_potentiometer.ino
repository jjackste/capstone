#include <Servo.h>

Servo myServo;
const int servoPin = 10;
const int potPin = A1;

int maxAngle = 130;
int minAngle = 60;
int setAngle = 0;

unsigned long currMillis;
unsigned long prevMillis = 0;
const unsigned long printInterval = 1000;  // Print printInterval in milliseconds
const unsigned long servoInterval = 10;    // Print   Interval in milliseconds


void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  pinMode(potPin, INPUT);
}

void loop() {
  // Updating the timing variable
  currMillis = millis();

  // Read the potentiometer and map its value (0-255) to servo angle (0-180)
  int potValue = analogRead(potPin);
  setAngle = map(potValue, 0, 1023, minAngle, maxAngle);


  // Set the servo position based on the potentiometer value allowing it time to move
  if (currMillis - prevMillis >= servoInterval) {
    myServo.write(setAngle);
  }

  // Print the current servo angle every 1000ms
  if (currMillis - prevMillis >= printInterval) {
    Serial.print("Servo angle: ");
    Serial.print(setAngle);
    Serial.println(" degrees.");
    prevMillis = currMillis;
  }
}
