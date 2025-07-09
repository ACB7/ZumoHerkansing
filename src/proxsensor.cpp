#include "proxsensor.h"

ProxSensor::ProxSensor()
    : centrumDetectieTeller(0), leftValue(0), rightValue(0) {}

void ProxSensor::init() {
    proxSensors.initFrontSensor();
}

void ProxSensor::read() {
    proxSensors.read();
    leftValue = proxSensors.countsFrontWithLeftLeds();
    rightValue = proxSensors.countsFrontWithRightLeds();
}

uint8_t ProxSensor::getLeft() {
    return leftValue;
}

uint8_t ProxSensor::getRight() {
    return rightValue;
}

bool ProxSensor::objectDetected() {
    return (leftValue >= sensorThreshold || rightValue >= sensorThreshold);
}

bool ProxSensor::centered() {
    // Beide sensoren detecteren evenveel en boven drempel -> mogelijk gecentreerd
    if (leftValue >= sensorThreshold && rightValue >= sensorThreshold && leftValue == rightValue) {
        centrumDetectieTeller++;
        if (centrumDetectieTeller >= nodigAantalCentrums) {
            centrumDetectieTeller = 0;
            return true;
        }
    } else {
        centrumDetectieTeller = 0;
    }
    return false;
}

void ProxSensor::resetCentrumTeller() {
    centrumDetectieTeller = 0;
}