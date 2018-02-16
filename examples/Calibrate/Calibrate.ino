/*
   TegHarvester class example
   @description Example showing how to calibrate the MCU reading with known input voltage
   @author Kristian Korsgaard
   @version 1.0
*/

#include <TegHarvester.h>

TegHarvester Teg; // Initialize Teg harvester object
                  // See header file for options

void setup() {
  Teg.begin(); // Initialize Teg
  Serial.begin(9600);
  
  // Calibrate MCU
  Teg.calibrate(2.5, 100, true); // Known input voltage of 2.5V on read voltage pin,
                                 // run 100 times and autoset offset on device (true)
}

void loop() {
}
