/*
   TegHarvester class example
   @description Simple example to showcase the TegHarvester class
   @author Kristian Korsgaard
   @version 1.0
*/

#include <TegHarvester.h>

TegHarvester Teg; // Initialize Teg harvester object
                  // See header file for options

void setup() {
  Teg.begin(); // Initialize outputs
  Serial.begin(9600);
}

void loop() {
  // Enable sample pin
  Teg.enableSample();

  // Get sample of Storage Voltage and print to serial with tree decimals
  Serial.println(Teg.getSample(), 3);

  // Disable sample pin
  Teg.disableSample();
  delay(1000);
}
