/*
  TegHarvester.h - Library for controlling the iDemoLab TegHarvester
  Created by Kristian Korsgaard, February 12, 2018.
  Released into the public domain.
*/

#ifndef TEGHARVESTER_H
#define TEGHARVESTER_H

#include "Arduino.h"

class TegHarvester
{
public:
  TegHarvester(byte keepAlivePin=17 /* Digital (A3) */, byte enableSamplePin=6 /* Digital (D6) */, byte storageVoltagePinA=6 /* Analog (A6) */);

  void enableSample();
  void disableSample();
  void toggleSample();

  double getSample() const;
  void setSample(double sample);

  void setAnalogReference(double aref = 3.3);
  void getAnalogReference() const;

  void keepAlive(bool alive = true);

private:
  void readVoltage();
  byte keepAlivePin_, enableSamplePin_, storageVoltagePinA_;
  double sample_;
  bool sampleState_;
  double aref_, arefStep_;
};

#endif /* end of include guard: TEGHARVESTER_HPP */
