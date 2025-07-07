#include "Motors.h"
#include <Zumo32U4.h>

Motors::Motors() : motors() {}

void Motors::vooruit(int snelheid) {
    motors.setSpeeds(snelheid, snelheid);
}

void Motors::stop() {
    motors.setSpeeds(0, 0);
}

void Motors::turnLeft(int snelheid) {
    motors.setSpeeds(-snelheid, snelheid);
}

void Motors::turnRight(int snelheid) {
    motors.setSpeeds(snelheid, -snelheid);
}

void Motors::gaNaarMidden(int snelheid, int duur) {
    motors.setSpeeds(snelheid, snelheid);
    delay(duur);
    motors.setSpeeds(0, 0);
}