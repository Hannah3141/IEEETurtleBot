#include <Arduino.h>
#include <Stepper.h>

// --- Hardware Pins ---
#define STEPS_PER_REV 200      // BY28 standard: 200 steps per revolution
#define MOTOR_PIN1 D2
#define MOTOR_PIN2 D3
#define MOTOR_PIN3 D4
#define MOTOR_PIN4 D5

#define RELAY_PIN D7           // Adjust to your actual relay pin

// --- Setup Stepper Motor ---
Stepper myStepper(STEPS_PER_REV, MOTOR_PIN1, MOTOR_PIN3, MOTOR_PIN2, MOTOR_PIN4);

void setup() {
  Serial.begin(115200);       // USB serial to Pi
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // relay off
  myStepper.setSpeed(60);     // RPM, adjust if needed
}

void loop() {
  if (Serial.available() >= 2) {  // command byte + data byte
    uint8_t cmd = Serial.read();
    uint8_t value = Serial.read();

    switch(cmd) {
      case 0x01:  // Move stepper
        myStepper.step((int)value); // simple step count
        Serial.write(0xAA);         // OK
        break;

      case 0x02:  // Relay
        if (value == 0x00) {
          digitalWrite(RELAY_PIN, LOW);
          Serial.write(0xAA);
        } else if (value == 0x01) {
          digitalWrite(RELAY_PIN, HIGH);
          Serial.write(0xAA);
        } else {
          Serial.write(0xFF);  // ERROR: invalid relay value
        }
        break;

      default:
        Serial.write(0xFF);      // ERROR: unknown command
        break;
    }
  }
}
