#ifndef BLOCKPUSH_H
#define BLOCKPUSH_H

#include <Zumo32U4.h>
#include "Motors.h"

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
  Zumo32U4ProximitySensors proxSensors;
  Zumo32U4ButtonA buttonA;
  Zumo32U4LineSensors lineSensors;
  Zumo32U4Buzzer buzzer;

  // Sensorconfiguratie
  static const uint8_t sensorThreshold = 2;
  static const uint16_t turnSpeedMax = 400;
  static const uint16_t turnSpeedMin = 400;
  static const uint16_t deceleration = 10;
  static const uint16_t acceleration = 10;
  static const unsigned long maxRamtijd = 2000;
  static const int MAXSNELHEID = 400;
  static const int AANTAL_LIJNSENSOREN = 5;

  unsigned int lineSensorValues[AANTAL_LIJNSENSOREN];

  // Draairichting
  bool senseDir;
  bool turningLeft;
  bool turningRight;

  // Snelheid en timers
  uint16_t turnSpeed;
  uint16_t lastTimeObjectSeen;
  unsigned long rammenStartTijd;

  // Eenmalige actie
  bool middenUitgevoerd;

  // Extra detectie voor gecentreerd object
  int centrumDetectieTeller;
  static const int nodigAantalCentrums = 3;
};

#endif