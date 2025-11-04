#include <ESP32Servo.h>

// === Pin Configuration ===
const int LDR_EAST = 25;   // East-facing LDR
const int LDR_WEST = 26;   // West-facing LDR
const int SERVO_PIN = 5;   // Servo control pin (PWM)

// === Servo Object ===
Servo sunflower;

// === Variables ===
int pos = 90;                // Start centered (90°)
int tolerance = 150;         // Minimum difference to trigger movement
int nightThreshold = 3000;    // When both LDRs read below this → Night mode
int stepSize = 3;            // How many degrees to move per update
int minPos = 30;              // Servo left limit
int maxPos = 170;            // Servo right limit

// === Setup ===
void setup() {
  Serial.begin(115200);
  delay(500);

  sunflower.setPeriodHertz(50);
  sunflower.attach(SERVO_PIN, 500, 2400);
  sunflower.write(pos);

  Serial.println("\n🌻 Smart Sunflower Tracker Started");
  Serial.println("System Calibrating... Ready!\n");
  delay(1000);
}

// === Function to average analog readings ===
int smoothRead(int pin) {
  long sum = 0;
  const int samples = 5;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(pin);
    delay(5);
  }
  return sum / samples;
}

// === Main Loop ===
void loop() {
  int east = smoothRead(LDR_EAST);
  int west = smoothRead(LDR_WEST);
  int diff = east - west;  // Positive = East brighter, Negative = West brighter

  // Print live readings
  Serial.print("East: "); Serial.print(east);
  Serial.print(" | West: "); Serial.print(west);
  Serial.print(" | Diff: "); Serial.print(diff);
  Serial.print(" | Servo Pos: "); Serial.print(pos);

  // === Night mode detection ===
  if (east > nightThreshold && west > nightThreshold) {
    // Both sides dark → move to rest
    pos = 90;
    sunflower.write(pos);
    Serial.println(" | 🌙 Night detected → Returning to center (90°)");
    delay(1000);
    return;
  }

  // === Light tracking ===
  if (abs(diff) < tolerance) {
    Serial.println(" | 🌼 Balanced light → Stable");
  } 
  else {
    if (diff > 0) {
      // East is brighter → rotate East
      pos -= stepSize;
      if (pos < minPos) pos = minPos;
      sunflower.write(pos);
      Serial.println(" | ☀️ East brighter → Turning East");
    } 
    else {
      // West is brighter → rotate West
      pos += stepSize;
      if (pos > maxPos) pos = maxPos;
      sunflower.write(pos);
      Serial.println(" | ☀️ West brighter → Turning West");
    }
  }

  delay(5);

}
