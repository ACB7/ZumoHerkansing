#include "blockpush.h"
#include "Motors.h"

blockpush::blockpush() :
  senseDir(true),
  turnSpeed(turnSpeedMax), lastTimeObjectSeen(0), rammenStartTijd(0),
  state(ZOEKEN), middenUitgevoerd(false),
  motors(), proxSensor() {}

void blockpush::setup() {
  Serial1.begin(9600);
  proxSensor.init();
  lineSensors.initFiveSensors();

  Serial1.print(F("Druk op knop A om te starten..."));
  buttonA.waitForButton();

  motors.vooruit(MAXSNELHEID);
  delay(1000);
  motors.stop();
}

void blockpush::loop() {
  if (!middenUitgevoerd) {
    motors.gaNaarMidden(200, 700); // snelheid 200, duur 700ms
    middenUitgevoerd = true;
  }

  proxSensor.read();
  lineSensors.read(lineSensorValues);
  uint8_t leftValue = proxSensor.getLeft();
  uint8_t rightValue = proxSensor.getRight();
  bool objectSeen = proxSensor.objectDetected();

  switch (state) {
    case ZOEKEN:
      if (objectSeen) {
        lastTimeObjectSeen = millis();
        turnSpeed = constrain(turnSpeed - deceleration, turnSpeedMin, turnSpeedMax);

        if (leftValue < rightValue) {
          motors.turnRight(turnSpeed);
          senseDir = true;
          proxSensor.resetCentrumTeller();
        } else if (leftValue > rightValue) {
          motors.turnLeft(turnSpeed);
          senseDir = false;
          proxSensor.resetCentrumTeller();
        } else if (proxSensor.centered()) {
          motors.vooruit(MAXSNELHEID);
          delay(150);
          rammenStartTijd = millis();
          state = RAMMEN;
        }
      } else {
        proxSensor.resetCentrumTeller();
        turnSpeed = constrain(turnSpeed + acceleration, turnSpeedMin, turnSpeedMax);
        (senseDir) ? motors.turnRight(turnSpeed) : motors.turnLeft(turnSpeed);
      }
      break;

    case RAMMEN:
      motors.vooruit(MAXSNELHEID);

      if (lineSensorValues[0] > 1000 || lineSensorValues[4] > 1000) {
        state = STOPPEN;
        delay(150);
        motors.stop();
      }

      if (millis() - rammenStartTijd > maxRamtijd) {
        state = STOPPEN;
        motors.stop();
      }
      break;

    case STOPPEN:
      // Geen verdere acties
      break;
  }
}
