#include <ESP32Servo.h>

// === Pin Configuration ===
const int LDR_RIGHT = 32;   // Right-facing LDR (was East)
const int LDR_LEFT = 34;    // Left-facing LDR (was West)
const int SERVO_PIN = 4;    // Servo control pin (PWM)

// === Servo Object ===
Servo sunflower;

// === Variables ===
int pos = 90;                // Start centered (90°)
int tolerance = 150;         // Minimum difference to trigger movement
int nightThreshold = 3000;   // When both LDRs read below this → Night mode
int stepSize = 3;            // How many degrees to move per update
int minPos = 30;             // Servo left limit
int maxPos = 170;            // Servo right limit

// === Setup ===
void setup() {
  Serial.begin(115200);
  delay(500);

  sunflower.setPeriodHertz(50);
  sunflower.attach(SERVO_PIN, 500, 2400);
  sunflower.write(pos);  // Start at center

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
  int right = smoothRead(LDR_RIGHT);
  int left = smoothRead(LDR_LEFT);
  int diff = right - left;  // Positive = Right brighter, Negative = Left brighter

  // Print live readings
  Serial.print("Right: "); Serial.print(right);
  Serial.print(" | Left: "); Serial.print(left);
  Serial.print(" | Diff: "); Serial.print(diff);
  Serial.print(" | Servo Pos: "); Serial.print(pos);

  // === Night mode detection ===
  if (right > nightThreshold && left > nightThreshold) {
    // Both sides dark → move back to center

    sunflower.write(90);
    Serial.println(" | 🌙 No light → Returning to center (90°)");
    delay(1000);
    return;
  }

  // === Light tracking ===
  if (abs(diff) < tolerance) {
    Serial.println(" | 🌼 Balanced light → Stable");
  } 
  else {
    if (diff > 0) {
      // Right is brighter → rotate right
      pos -= stepSize;
      if (pos < minPos) pos = minPos;
      sunflower.write(pos);
      Serial.println(" | ☀️ Right brighter → Turning Right");
    } 
    else {
      // Left is brighter → rotate left
      pos += stepSize;
      if (pos > maxPos) pos = maxPos;
      sunflower.write(pos);
      Serial.println(" | ☀️ Left brighter → Turning Left");
    }
  }

  delay(5);
}
