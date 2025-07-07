#include "blockpush.h"
#include "Motors.h"

blockpush::blockpush() :
  senseDir(true), turningLeft(false), turningRight(false),
  turnSpeed(turnSpeedMax), lastTimeObjectSeen(0), rammenStartTijd(0),
  state(ZOEKEN), middenUitgevoerd(false), centrumDetectieTeller(0),
  motors() {}

void blockpush::setup() {
  Serial1.begin(9600);
  proxSensors.initFrontSensor();
  lineSensors.initFiveSensors();

  Serial1.print(F("Druk op knop A om te starten..."));
  buttonA.waitForButton();

  motors.vooruit(MAXSNELHEID);
  delay(1000);
  motors.stop();
}

void blockpush::loop() {
  if (!middenUitgevoerd) {
    motors.gaNaarMidden(100, 600); // snelheid 100, duur 600ms
    middenUitgevoerd = true;
  }

  proxSensors.read();
  lineSensors.read(lineSensorValues);
  uint8_t leftValue = proxSensors.countsFrontWithLeftLeds();
  uint8_t rightValue = proxSensors.countsFrontWithRightLeds();
  bool objectSeen = (leftValue >= sensorThreshold || rightValue >= sensorThreshold);

  switch (state) {
    case ZOEKEN:
      if (objectSeen) {
        lastTimeObjectSeen = millis();
        turnSpeed = constrain(turnSpeed - deceleration, turnSpeedMin, turnSpeedMax);

        if (leftValue < rightValue) {
          motors.turnRight(turnSpeed);
          senseDir = true;
          centrumDetectieTeller = 0;
        } else if (leftValue > rightValue) {
          motors.turnLeft(turnSpeed);
          senseDir = false;
          centrumDetectieTeller = 0;
        } else if (leftValue >= sensorThreshold && rightValue >= sensorThreshold) {
          // Beide sensoren detecteren evenveel: mogelijk gecentreerd
          centrumDetectieTeller++;
          if (centrumDetectieTeller >= nodigAantalCentrums) {
            motors.vooruit(MAXSNELHEID);
            delay(150);  // Extra zekerheid voor centrering
            rammenStartTijd = millis();
            state = RAMMEN;
            centrumDetectieTeller = 0;
          }
        }
      } else {
        centrumDetectieTeller = 0;
        turnSpeed = constrain(turnSpeed + acceleration, turnSpeedMin, turnSpeedMax);
        (senseDir) ? motors.turnRight(turnSpeed) : motors.turnLeft(turnSpeed);
      }
      break;

    case RAMMEN:
      motors.vooruit(MAXSNELHEID);

      if (lineSensorValues[0] > 1000 || lineSensorValues[4] > 1000) {
        state = STOPPEN;
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