/*
 * This ESP8266 NodeMCU code was developed by newbiely.com
 *
 * This ESP8266 NodeMCU code is made available for public use without any restriction
 *
 * For comprehensive instructions and wiring diagrams, please visit:
 * https://newbiely.com/tutorials/esp8266/esp8266-potentiometer
 */

#define POTENTIOMETER_PIN A0


float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// The setup function runs once on reset or power-up
void setup() {
  // Initialize the Serial to communicate with the Serial Monitor.
  Serial.begin(115200);
  delay(200);
  Serial.println();
  Serial.println("20 turns counterclockwise");
  
}

// The loop function repeats indefinitely.
void loop() {
  // read the input on analog pin:
  int analog_value = analogRead(POTENTIOMETER_PIN);
  // Rescale to potentiometer's voltage (from 0V to 5V):
  float voltage = floatMap(analog_value, 0, 1023, 0, 5);

  // print out the value you read:
  Serial.print("Analog: ");
  Serial.print(analog_value);
  Serial.print(", Voltage: ");
  Serial.println(voltage);
  delay(1000);
}
