#include <Servo.h>

// Hardware
Servo myServo;
const int servoPin = 10;
const int potPin = A1;

// Servo angles
const int closedAngle = 130;  // Closed position
const int openAngle = 60;     // Open position
int setAngle = closedAngle;   // Start with valve closed

// Timing
unsigned long currMillis;
unsigned long prevServoMillis = 0;
unsigned long prevPrintMillis = 0;
const unsigned long printInterval = 500;  // Print interval in milliseconds
const unsigned long servoInterval = 10;    // Servo update interval in milliseconds

// Unlocking logic
bool unlocked = false; // start unlocked
int unlockStage = 0;  // 0 = Locked, 1 = Open reached, 2 = Closed reached (Unlocked)

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  pinMode(potPin, INPUT);

  // Start with valve closed
  myServo.write(closedAngle);
  Serial.println("Valve locked: Waiting for unlock sequence");
}

void loop() {
  currMillis = millis();
  
  // Read and map the potentiometer value
  int potValue = analogRead(potPin);
  int mappedAngle = map(potValue, 0, 1023, openAngle, closedAngle);

  // Unlock logic
  if (!unlocked) {
    if (unlockStage == 0 && mappedAngle <= openAngle + 5) {
      unlockStage = 1;  // Fully opened
      Serial.println("Step 1: Valve fully open.");
    }
    if (unlockStage == 1 && mappedAngle >= closedAngle - 5) {
      unlockStage = 2;  // Fully closed → Unlock
      unlocked = true;
      Serial.println("Valve unlocked: Now controlled by potentiometer");
    }
  }

  // Control servo only if unlocked
  if (unlocked && currMillis - prevServoMillis >= servoInterval) {
    prevServoMillis = currMillis;
    if (mappedAngle != setAngle) { // Update only if angle changed
      setAngle = mappedAngle;
      myServo.write(setAngle);
    }
  }

  // **Ensure Serial Monitor prints every second**
  if (currMillis - prevPrintMillis >= printInterval) {
    prevPrintMillis = currMillis;
    Serial.print("Servo angle: ");
    Serial.print(setAngle);
    Serial.print(" degrees. ");
    Serial.println(unlocked ? "Valve unlocked." : "Waiting for unlock sequence");
  }
}
