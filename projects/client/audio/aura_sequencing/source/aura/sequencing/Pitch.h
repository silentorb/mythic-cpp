#pragma once

#include <aura/sequencing/Key.h>
#include "commoner/dllexport.h"

namespace aura {
  namespace sequencing {

  struct Pitch {
      const int index;
      const float frequency;
      const char *name;
      const Key key;
  };

  namespace pitches {
    extern const Pitch GSN1;
    extern const Pitch A0;
    extern const Pitch AS0;
    extern const Pitch B0;
    extern const Pitch C1;
    extern const Pitch CS1;
    extern const Pitch D1;
    extern const Pitch DS1;
    extern const Pitch E1;
    extern const Pitch F1;
    extern const Pitch FS1;
    extern const Pitch G1;
    extern const Pitch GS1;
    extern const Pitch A1;
    extern const Pitch AS1;
    extern const Pitch B1;
    extern const Pitch C2;
    extern const Pitch CS2;
    extern const Pitch D2;
    extern const Pitch DS2;
    extern const Pitch E2;
    extern const Pitch F2;
    extern const Pitch FS2;
    extern const Pitch G2;
    extern const Pitch GS2;
    extern const Pitch A2;
    extern const Pitch AS2;
    extern const Pitch B2;
    extern const Pitch C3;
    extern const Pitch CS3;
    extern const Pitch D3;
    extern const Pitch DS3;
    extern const Pitch E3;
    extern const Pitch F3;
    extern const Pitch FS3;
    extern const Pitch G3;
    extern const Pitch GS3;
    extern const Pitch A3;
    extern const Pitch AS3;
    extern const Pitch B3;
    extern const Pitch C4;
    extern const Pitch CS4;
    extern const Pitch D4;
    extern const Pitch DS4;
    extern const Pitch E4;
    extern const Pitch F4;
    extern const Pitch FS4;
    extern const Pitch G4;
    extern const Pitch GS4;
    extern const Pitch A4;
    extern const Pitch AS4;
    extern const Pitch B4;
    extern const Pitch C5;
    extern const Pitch CS5;
    extern const Pitch D5;
    extern const Pitch DS5;
    extern const Pitch E5;
    extern const Pitch F5;
    extern const Pitch FS5;
    extern const Pitch G5;
    extern const Pitch GS5;
    extern const Pitch A5;
    extern const Pitch AS5;
    extern const Pitch B5;
    extern const Pitch C6;
    extern const Pitch CS6;
    extern const Pitch D6;
    extern const Pitch DS6;
    extern const Pitch E6;
    extern const Pitch F6;
    extern const Pitch FS6;
    extern const Pitch G6;
    extern const Pitch GS6;
    extern const Pitch A6;
    extern const Pitch AS6;
    extern const Pitch B6;
    extern const Pitch C7;
    extern const Pitch CS7;
    extern const Pitch D7;
    extern const Pitch DS7;
    extern const Pitch E7;
    extern const Pitch F7;
    extern const Pitch FS7;
    extern const Pitch G7;
    extern const Pitch GS7;
    extern const Pitch A7;
    extern const Pitch AS7;
    extern const Pitch B7;
    extern const Pitch C8;
  }

  const int PITCH_COUNT = 89;
  extern const Pitch Pitches[PITCH_COUNT];
}}
