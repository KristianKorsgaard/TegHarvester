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
  TegHarvester::TegHarvester(
    byte keepAlivePin=17 /* Digital (A3) */,
    byte enableSamplePin=6 /* Digital */,
    byte storageVoltagePinA=6 /* Analog */,
    double aref=3.3 /* Analog Reference Voltage */);

  // Run to initialize digital ports
  void begin();

  // Enable sample on TegHarvester
  void enableSample();
  void disableSample();
  void toggleSample();

  // Read Voltage sample from TegHarvester if "enableSample" is set,
  // otherwise return sample from memory
  double getSample() const;
  // Set sample in memory
  void setSample(double sample = 0.0);

  // Set analog reference value to calculate voltage sampleState_
  // Use in conjunction with analogReference() in Arduino IDE
  void setAnalogReference(double aref = 3.3);
  // Return stored analog reference
  void getAnalogReference() const;

  // Set keep_alive on TegHarvester, to keep Core alive
  void keepAlive(bool alive = true);

  // Set offset for analog read, to calibrate measurements (samples)
  // The analog read return a value between 0-1023, to which this value is added
  void setOffset(char offset = -4);
  char getOffset() const;

  // Calibrate MCU with known input voltage
  void calibrate(double aim, int runs, bool autoOffset = false);

private:
  void readVoltage();
  byte keepAlivePin_, enableSamplePin_, storageVoltagePinA_;
  double sample_;
  bool sampleState_;
  double aref_, arefStep_;
  byte offset_;
};

#endif /* end of include guard: TEGHARVESTER_HPP */
