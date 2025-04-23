#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

float lastAngle = 0;
float unwrappedAngle = 0;

float unwrapAngle(float current, float previous) {
  float diff = current - previous;
  if (diff > 180) diff -= 360;
  else if (diff < -180) diff += 360;
  return previous + diff;
}

void setup() {
  Serial.begin(9600);
  if (!bno.begin()) {
    Serial.println("No BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  delay(1000);
  bno.setExtCrystalUse(true);
}

void loop() {
  sensors_event_t event;
  bno.getEvent(&event);

  float currentAngle = event.orientation.x;
  unwrappedAngle = unwrapAngle(currentAngle, lastAngle);
  lastAngle = unwrappedAngle;

  Serial.println(unwrappedAngle);
  delay(100);
}

