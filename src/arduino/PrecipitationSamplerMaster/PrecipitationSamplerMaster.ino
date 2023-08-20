/*
This ATmega controls the following:
  1) Sleep timer (RTC)
  2) Lid open close
  3) SD-card

With this, it becomes the master. It can perform all the nessesary tasks for rain detection, start collecting and write data to the SD-card.

It will first wake up periodicly to make sure the sampling only happens every 2 weeks.
After that the sleep cycles are short, where it will check if rain/snow is falling.
In case it does, it opens the lid to start collecting water/snow for 4 hours.
When the 4 hours is done, it will close the lid, and turn on the rest of the system to start the sampling process.
When this board recieves info, that the sampling is done, it will go to sleep and the cycle repeats.

By:
Mads Rosenhøj Jeppesen
Aarhus University
2023

*/
#include "./modules/setup/modules.h"

void setup() {
  SystemEnablePrimary();  // Primary systems (Pins, SDcard, RTC)

  while (!LidHome()) {
    ;  // Wait for homine to finish
  }

  ResetSample();
}

void loop() {
  SamplingProcess();  // Sleep and Sample Process
}