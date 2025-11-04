#include <ESP32Servo.h>

const int SERVO1_PIN = 4;  // First servo signal pin
const int SERVO2_PIN = 5;  // Second servo signal pin

Servo servo1;
Servo servo2;

void setup() {
  Serial.begin(115200);
  delay(500);

  servo1.setPeriodHertz(50);
  servo2.setPeriodHertz(50);

  servo1.attach(SERVO1_PIN, 500, 2400);
  servo2.attach(SERVO2_PIN, 500, 2400);

  Serial.println("=== Dual Servo Motor Test ===");
  Serial.println("Servo1 on pin 4 and Servo2 on pin 5 will sweep together.");
}

void loop() {
  // Sweep 0° → 180°
  for (int pos = 0; pos <= 180; pos += 5) {
    servo1.write(pos);
    servo2.write(pos);
    Serial.print("Position: ");
    Serial.println(pos);
    delay(100);
  }

  // Sweep 180° → 0°
  for (int pos = 180; pos >= 0; pos -= 5) {
    servo1.write(pos);
    servo2.write(pos);
    Serial.print("Position: ");
    Serial.println(pos);
    delay(100);
  }

  Serial.println("One full sweep completed!\n");
  delay(1000);
}

