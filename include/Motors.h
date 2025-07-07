#ifndef MOTORS_H
#define MOTORS_H

#include <Zumo32U4.h>

class Motors {
public:
    Motors();
    void vooruit(int snelheid);
    void stop();
    void turnLeft(int snelheid);
    void turnRight(int snelheid);
    void gaNaarMidden(int snelheid, int duur);

private:
    Zumo32U4Motors motors;
};

#endif