#include <AccelStepper.h>

// Stepper pins
#define IN1 D2
#define IN2 D3
#define IN3 D4
#define IN4 D5

// Relay pin
#define RELAY_PIN D7

// 28BYJ-48 half-step mode
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // relay OFF (active LOW)

  stepper.setMaxSpeed(800);
  stepper.setAcceleration(400);

  Serial.println("ESP32 Ready");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd.startsWith("MOTOR")) {
      int steps = cmd.substring(6).toInt();
      stepper.move(steps);
      while (stepper.distanceToGo() != 0) {
        stepper.run();
      }
      Serial.println("MOTOR DONE");
    }

    else if (cmd == "RELAY ON") {
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("RELAY ON");
    }

    else if (cmd == "RELAY OFF") {
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("RELAY OFF");
    }
  }
}
