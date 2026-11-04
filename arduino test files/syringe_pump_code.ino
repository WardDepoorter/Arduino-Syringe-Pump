#include <AccelStepper.h>

const int stepsPerRevolution = 200;
const int CCW_TURNS = 20;
const int RPM_MIN = 3;
const int RPM_MAX = 15;

// Pin definitions for TMC2209 in STEP/DIR mode
#define STEP_PIN 21   // D1
#define DIR_PIN 20   // D2
#define ENABLE_PIN 22  // D5
//#define IN4 12  // D6

// Pin def for potentiometer
#define POT_PIN A0

// Initialize AccelStepper (DRIVER mode = 1)
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

long stepsLeft = (long)CCW_TURNS * stepsPerRevolution;  // 40960 steps

void releaseCoils() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void setup() {

  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, LOW); // Enable driver (active LOW)
  // Set max speed and acceleration (steps/sec and steps/sec^2)
  // 3200 steps/rev = 1/16 microstepping on a 200 step motor
  stepper.setMaxSpeed(1600); // 0.5 revs/sec
  stepper.setAcceleration(800); // Ramp up over 2 seconds
  
  //Serial.begin(115200);
  //delay(200);
  //Serial.println();
  //Serial.println("20 turns");
NEW SKETCH

}

void loop() {
  if (stepsLeft <= 0) return;

  int value = analogRead(POT_PIN);

  // direction from pot position, speed from the same value
  int sign = (value < 513) ? -1 : 1;
  if (value < 512){
    int current_rpm = map(value, 0, 512, RPM_MAX, RPM_MIN);
    myStepper.setSpeed(current_rpm);
    myStepper.step(sign * 8);
    stepsLeft -= 8;
    yield();

    Serial.print("speed: ");
    Serial.print(current_rpm);
    Serial.println(" rpm");}

  if (value >512 ){
    int current_rpm = map(value, 513, 1023, RPM_MIN, RPM_MAX);
    myStepper.setSpeed(current_rpm);

    myStepper.step(sign * 8);
    stepsLeft -= 8;
    yield();

    Serial.print("speed: ");
    Serial.print(current_rpm);
    Serial.println(" rpm");}

  if (stepsLeft <= 0) {
    stepsLeft = 0;
    releaseCoils();
    Serial.println("done");
  }
}