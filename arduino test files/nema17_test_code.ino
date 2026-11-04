#include <AccelStepper.h>

// Pin definitions for TMC2209 in STEP/DIR mode
#define STEP_PIN 3
#define DIR_PIN 2
#define ENABLE_PIN 12

// Initialize AccelStepper (DRIVER mode = 1)
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  //syring/motor specs:

  int steps_per_revolution = 200; // =motor spec, no microstepping
  float volume_per_step = 0.00615; //ml/step
  float volume_per_revolotion = steps_per_revolution *volume_per_step;
  
  //user inputs:

  float flowrate = 1 ; //ml/s 
  float volume_to_move = 20 ;//ml

  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, LOW); // Enable driver (active LOW)
  
  // Set max speed and acceleration (steps/sec and steps/sec^2)
  // 200 steps/rev 
  //int rpm = 10;
  float steps_per_second_from_flowrate = flowrate / volume_per_step; 
  stepper.setMaxSpeed(steps_per_second_from_flowrate); // 0.5 revs/sec
  stepper.setAcceleration(3200); // Ramp up over 2 seconds
  stepper.setCurrentPosition(0);
  float step_number_volume = volume_to_move /volume_per_step; // calc nr of stps for required volume
  stepper.moveTo(step_number_volume); // Move exactly 2 revolutions
}

void loop() {
  // Must be called as often as possible for smooth timing
  stepper.run();
  
  // Reverse direction when target is reached
  if (stepper.distanceToGo() == 0) {
    stepper.moveTo(-stepper.currentPosition());
  }
}