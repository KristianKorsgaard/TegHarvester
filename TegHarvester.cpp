/*
  TegHarvester.cpp - Library for controlling the iDemoLab TegHarvester
  Created by Kristian Korsgaard, February 12, 2018.
  Released into the public domain.
*/

#include "TegHarvester.h"

TegHarvester::TegHarvester(byte keepAlivePin=17 /* Digital (A3) */, byte enableSamplePin=6 /* Digital */, byte storageVoltagePinA=6 /* Analog */)
: keepAlivePin_(keepAlivePin), enableSamplePin_(enableSamplePin), storageVoltagePinA_(storageVoltagePinA)
{
  pinMode(keepAlivePin_, OUTPUT);
  pinMode(enableSamplePin_, OUTPUT);
}

void TegHarvester::enableSample()
{
  digitalWrite(enableSamplePin_, HIGH);
}
void TegHarvester::disableSample()
{
  digitalWrite(enableSamplePin_, LOW);
}
void TegHarvester::toggleSample()
{
  digitalWrite(enableSamplePin_, sampleState_ ? LOW : HIGH);
  sampleState_ = !sampleState_;
}

void TegHarvester::readVoltage()
{
  setSample(analogRead(storageVoltagePinA_) * arefStep_);
}
double TegHarvester::getSample() const
{
  if(sampleState_)
  {
    readVoltage();
  }
  return sample_;
}
void TegHarvester::setSample(double sample)
{
  if(sample < 0.0)
  {
    sample_ = 0.0;
  }
  else if(sample > aref)
  {
    sample_ = aref;
  }
  else
  {
    sample_ = sample;
  }
}

void TegHarvester::setAnalogReference(double aref = 3.3)
{
  if(aref > 0.0 && aref <= 5.0)
  {
    aref_ = aref;
    arefStep_ = aref_ / 1024;
  }
}
void TegHarvester::getAnalogReference() const
{
  return aref_;
}

void TegHarvester::keepAlive(bool alive = true)
{
  digitalWrite(keepAlivePin_, alive ? HIGH : LOW);
}
