#include <Arduino.h>
#include "config.h"
#include "motion.h" 
#include "limits.h"
#include "ui.h"



AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN); // Initialize AccelStepper (DRIVER mode = 1)
LiquidCrystal_I2C Status_LCD(0x27, 16, 2); // Creates I2C LCD Object With (Address=0x27, Cols=16, Rows=2)








void setup()
{
  Status_LCD.init();
  Status_LCD.backlight();
  Status_LCD.setCursor(0, 0);
  Status_LCD.print("Hello World!!");
  Status_LCD.setCursor(0, 1);
  Status_LCD.print("Syringe pump test");  
  Serial.begin(9600);
}

void loop()
{
    Serial.println("Hello world!");
    delay(1000);
}