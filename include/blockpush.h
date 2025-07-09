#ifndef BLOCKPUSH_H
#define BLOCKPUSH_H

#include <Zumo32U4.h>
#include "Motors.h"
#include "proxsensor.h"

class blockpush {
public:
  blockpush();
  void setup();
  void loop();

private:
  enum State { ZOEKEN, RAMMEN, STOPPEN };
  State state;


  // Hardware
  Motors motors;
  ProxSensor proxSensor;
  Zumo32U4ButtonA buttonA;
  Zumo32U4LineSensors lineSensors;
  Zumo32U4Buzzer buzzer;

  // Sensorconfiguratie
  static const uint16_t turnSpeedMax = 200;
  static const uint16_t turnSpeedMin = 120;        // Lager dan max!
  static const uint16_t deceleration = 10;         // Kleiner = vloeiender
  static const uint16_t acceleration = 10;         // Kleiner = vloeiender
  static const unsigned long maxRamtijd = 3000;   // 15 seconden rammen!
  static const int MAXSNELHEID = 400;
  static const int AANTAL_LIJNSENSOREN = 5;

  unsigned int lineSensorValues[AANTAL_LIJNSENSOREN];

  // Draairichting
  bool senseDir;

  // Snelheid en timers
  uint16_t turnSpeed;
  uint16_t lastTimeObjectSeen;
  unsigned long rammenStartTijd;

  // Eenmalige actie
  bool middenUitgevoerd;
};

#endif