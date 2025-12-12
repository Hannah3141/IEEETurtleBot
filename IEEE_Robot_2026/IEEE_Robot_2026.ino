#include <Stepper.h>

#define RELAY D5
#define STEP_PER_REVOLUTION 2048  // for 28BYJ-48 stepper

Stepper stepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  stepper.setSpeed(10);  //RPM
}

void loop() {
  if (Serial.available()) {
    String piCommand = Serial.readStringUntil('\n');

    if (piCommand == "RELAY_ON") {
    digitalWrite(RELAY, HIGH);
    } else if (piCommand == "RELAY_OFF") {
      digitalWrite(relayPin, LOW);
    } else if (piCommand.startsWith("MOVE")) {
      int steps = piCommand.substring(5).toInt();
      stepper.step(steps);
    }
  }
}
