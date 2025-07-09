#ifndef PROXSENSOR_H
#define PROXSENSOR_H

#include <Zumo32U4.h>

class ProxSensor {
public:
    ProxSensor();
    void init();
    void read();
    bool objectDetected();
    bool centered();
    uint8_t getLeft();
    uint8_t getRight();
    void resetCentrumTeller();

private:
    Zumo32U4ProximitySensors proxSensors;
    static const uint8_t sensorThreshold = 2;
    int centrumDetectieTeller;
    static const int nodigAantalCentrums = 3;
    uint8_t leftValue;
    uint8_t rightValue;
};

#endif