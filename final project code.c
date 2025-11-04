#include <ESP32Servo.h>

// === Pin Configuration ===
// Code 1 pins
const int LDR_RIGHT = 34;   // Right-facing LDR
const int LDR_LEFT  = 32;   // Left-facing LDR
const int SERVO_PIN1 = 4;   // Servo pin from Code 1

// Code 2 pins
const int LDR_EAST = 25;    // East-facing LDR
const int LDR_WEST = 26;    // West-facing LDR
const int SERVO_PIN2 = 5;   // Servo pin from Code 2

// === Servo Objects ===
Servo sunflower1;  // For Code 1
Servo sunflower2;  // For Code 2

// === Variables ===
int pos1 = 90;      // Servo 1 start position
int pos2 = 90;      // Servo 2 start position
int tolerance = 150;
int nightThreshold = 3000;
int stepSize = 3;
int minPos = 30;
int maxPos = 170;

// === Setup ===
void setup() {
  Serial.begin(115200);
  delay(500);

  // Attach servos
  sunflower1.setPeriodHertz(50);
  sunflower1.attach(SERVO_PIN1, 500, 2400);
  sunflower1.write(pos1);

  sunflower2.setPeriodHertz(50);
  sunflower2.attach(SERVO_PIN2, 500, 2400);
  sunflower2.write(pos2);

  Serial.println("\n🌻 Smart Sunflower Tracker Merged Version Started");
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
  // --- Code 1 tracking (Right/Left) ---
  int right = smoothRead(LDR_RIGHT);
  int left  = smoothRead(LDR_LEFT);
  int diff1 = right - left;

  Serial.print("Code1 | Right: "); Serial.print(right);
  Serial.print(" | Left: "); Serial.print(left);
  Serial.print(" | Diff: "); Serial.print(diff1);
  Serial.print(" | Servo Pos: "); Serial.println(pos1);

  if (right > nightThreshold && left > nightThreshold) {
    pos1 = 90;
    sunflower1.write(pos1);
    Serial.println("🌙 Code1 Night → Servo back to center");
  } else if (abs(diff1) < tolerance) {
    Serial.println("🌼 Code1 Balanced light → Stable");
  } else {
    if (diff1 > 0) {
      pos1 -= stepSize;
      if (pos1 < minPos) pos1 = minPos;
      sunflower1.write(pos1);
      Serial.println("☀️ Code1 Right brighter → Turning Right");
    } else {
      pos1 += stepSize;
      if (pos1 > maxPos) pos1 = maxPos;
      sunflower1.write(pos1);
      Serial.println("☀️ Code1 Left brighter → Turning Left");
    }
  }

  // --- Code 2 tracking (East/West) ---
  int east = smoothRead(LDR_EAST);
  int west = smoothRead(LDR_WEST);
  int diff2 = east - west;

  Serial.print("Code2 | East: "); Serial.print(east);
  Serial.print(" | West: "); Serial.print(west);
  Serial.print(" | Diff: "); Serial.print(diff2);
  Serial.print(" | Servo Pos: "); Serial.println(pos2);

  if (east > nightThreshold && west > nightThreshold) {
    pos2 = 90;
    sunflower2.write(pos2);
    Serial.println("🌙 Code2 Night → Servo back to center");
  } else if (abs(diff2) < tolerance) {
    Serial.println("🌼 Code2 Balanced light → Stable");
  } else {
    if (diff2 > 0) {
      pos2 -= stepSize;
      if (pos2 < minPos) pos2 = minPos;
      sunflower2.write(pos2);
      Serial.println("☀️ Code2 East brighter → Turning East");
    } else {
      pos2 += stepSize;
      if (pos2 > maxPos) pos2 = maxPos;
      sunflower2.write(pos2);
      Serial.println("☀️ Code2 West brighter → Turning West");
    }
  }

  delay(5);
}
