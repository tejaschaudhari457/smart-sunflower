// === Pin Configuration ===
const int LDR1 = 32;   // LDR 1
const int LDR2 = 34;   // LDR 2
const int LDR3 = 25;   // LDR 3
const int LDR4 = 26;   // LDR 4

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("=== 4 LDR Sensor Test ===");
  Serial.println("Reading analog values from all 4 LDRs...\n");
}

void loop() {
  int ldr1 = analogRead(LDR1);
  int ldr2 = analogRead(LDR2);
  int ldr3 = analogRead(LDR3);
  int ldr4 = analogRead(LDR4);

  // Print all readings
  Serial.print("LDR1 (Pin 32): "); Serial.print(ldr1);
  Serial.print(" | LDR2 (Pin 34): "); Serial.print(ldr2);
  Serial.print(" | LDR3 (Pin 25): "); Serial.print(ldr3);
  Serial.print(" | LDR4 (Pin 26): "); Serial.println(ldr4);

  delay(500); // Update every 0.5 seconds
}
