/*
  TegHarvester.cpp - Library for controlling the iDemoLab TegHarvester
  Created by Kristian Korsgaard, February 12, 2018.
  Released into the public domain.
*/

#include "TegHarvester.h"

TegHarvester::TegHarvester(byte keepAlivePin, byte enableSamplePin, byte storageVoltagePinA, double aref)
: keepAlivePin_(keepAlivePin), enableSamplePin_(enableSamplePin), storageVoltagePinA_(storageVoltagePinA)
{
  setAnalogReference(aref);
  setOffset();
  setSample();
}

void TegHarvester::begin()
{
  pinMode(keepAlivePin_, OUTPUT);
  pinMode(enableSamplePin_, OUTPUT);
}

void TegHarvester::enableSample()
{
  digitalWrite(enableSamplePin_, HIGH);
  sampleState_ = true;
}
void TegHarvester::disableSample()
{
  digitalWrite(enableSamplePin_, LOW);
  sampleState_ = false;
}
void TegHarvester::toggleSample()
{
  digitalWrite(enableSamplePin_, sampleState_ ? LOW : HIGH);
  sampleState_ = !sampleState_;
}

void TegHarvester::readVoltage()
{
  unsigned int v = analogRead(storageVoltagePinA_);
  v += getOffset();
  setSample( v * arefStep_ );
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
  else if(sample > aref_)
  {
    sample_ = aref_;
  }
  else
  {
    sample_ = sample;
  }
}

void TegHarvester::setAnalogReference(double aref)
{
  if(aref > 0.0 && aref <= 5.0)
  {
    aref_ = aref;
    arefStep_ = aref_ / 1024;
  }
  else
  {
    aref = 3.3;
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

void TegHarvester::setOffset(char offset)
{
  offset_ = offset;
}
char TegHarvester::getOffset() const
{
  return offset_;
}
