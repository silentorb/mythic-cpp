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
    SEQUENCING_EXPORT extern const Pitch GSN1;
    SEQUENCING_EXPORT extern const Pitch A0;
    SEQUENCING_EXPORT extern const Pitch AS0;
    SEQUENCING_EXPORT extern const Pitch B0;
    SEQUENCING_EXPORT extern const Pitch C1;
    SEQUENCING_EXPORT extern const Pitch CS1;
    SEQUENCING_EXPORT extern const Pitch D1;
    SEQUENCING_EXPORT extern const Pitch DS1;
    SEQUENCING_EXPORT extern const Pitch E1;
    SEQUENCING_EXPORT extern const Pitch F1;
    SEQUENCING_EXPORT extern const Pitch FS1;
    SEQUENCING_EXPORT extern const Pitch G1;
    SEQUENCING_EXPORT extern const Pitch GS1;
    SEQUENCING_EXPORT extern const Pitch A1;
    SEQUENCING_EXPORT extern const Pitch AS1;
    SEQUENCING_EXPORT extern const Pitch B1;
    SEQUENCING_EXPORT extern const Pitch C2;
    SEQUENCING_EXPORT extern const Pitch CS2;
    SEQUENCING_EXPORT extern const Pitch D2;
    SEQUENCING_EXPORT extern const Pitch DS2;
    SEQUENCING_EXPORT extern const Pitch E2;
    SEQUENCING_EXPORT extern const Pitch F2;
    SEQUENCING_EXPORT extern const Pitch FS2;
    SEQUENCING_EXPORT extern const Pitch G2;
    SEQUENCING_EXPORT extern const Pitch GS2;
    SEQUENCING_EXPORT extern const Pitch A2;
    SEQUENCING_EXPORT extern const Pitch AS2;
    SEQUENCING_EXPORT extern const Pitch B2;
    SEQUENCING_EXPORT extern const Pitch C3;
    SEQUENCING_EXPORT extern const Pitch CS3;
    SEQUENCING_EXPORT extern const Pitch D3;
    SEQUENCING_EXPORT extern const Pitch DS3;
    SEQUENCING_EXPORT extern const Pitch E3;
    SEQUENCING_EXPORT extern const Pitch F3;
    SEQUENCING_EXPORT extern const Pitch FS3;
    SEQUENCING_EXPORT extern const Pitch G3;
    SEQUENCING_EXPORT extern const Pitch GS3;
    SEQUENCING_EXPORT extern const Pitch A3;
    SEQUENCING_EXPORT extern const Pitch AS3;
    SEQUENCING_EXPORT extern const Pitch B3;
    SEQUENCING_EXPORT extern const Pitch C4;
    SEQUENCING_EXPORT extern const Pitch CS4;
    SEQUENCING_EXPORT extern const Pitch D4;
    SEQUENCING_EXPORT extern const Pitch DS4;
    SEQUENCING_EXPORT extern const Pitch E4;
    SEQUENCING_EXPORT extern const Pitch F4;
    SEQUENCING_EXPORT extern const Pitch FS4;
    SEQUENCING_EXPORT extern const Pitch G4;
    SEQUENCING_EXPORT extern const Pitch GS4;
    SEQUENCING_EXPORT extern const Pitch A4;
    SEQUENCING_EXPORT extern const Pitch AS4;
    SEQUENCING_EXPORT extern const Pitch B4;
    SEQUENCING_EXPORT extern const Pitch C5;
    SEQUENCING_EXPORT extern const Pitch CS5;
    SEQUENCING_EXPORT extern const Pitch D5;
    SEQUENCING_EXPORT extern const Pitch DS5;
    SEQUENCING_EXPORT extern const Pitch E5;
    SEQUENCING_EXPORT extern const Pitch F5;
    SEQUENCING_EXPORT extern const Pitch FS5;
    SEQUENCING_EXPORT extern const Pitch G5;
    SEQUENCING_EXPORT extern const Pitch GS5;
    SEQUENCING_EXPORT extern const Pitch A5;
    SEQUENCING_EXPORT extern const Pitch AS5;
    SEQUENCING_EXPORT extern const Pitch B5;
    SEQUENCING_EXPORT extern const Pitch C6;
    SEQUENCING_EXPORT extern const Pitch CS6;
    SEQUENCING_EXPORT extern const Pitch D6;
    SEQUENCING_EXPORT extern const Pitch DS6;
    SEQUENCING_EXPORT extern const Pitch E6;
    SEQUENCING_EXPORT extern const Pitch F6;
    SEQUENCING_EXPORT extern const Pitch FS6;
    SEQUENCING_EXPORT extern const Pitch G6;
    SEQUENCING_EXPORT extern const Pitch GS6;
    SEQUENCING_EXPORT extern const Pitch A6;
    SEQUENCING_EXPORT extern const Pitch AS6;
    SEQUENCING_EXPORT extern const Pitch B6;
    SEQUENCING_EXPORT extern const Pitch C7;
    SEQUENCING_EXPORT extern const Pitch CS7;
    SEQUENCING_EXPORT extern const Pitch D7;
    SEQUENCING_EXPORT extern const Pitch DS7;
    SEQUENCING_EXPORT extern const Pitch E7;
    SEQUENCING_EXPORT extern const Pitch F7;
    SEQUENCING_EXPORT extern const Pitch FS7;
    SEQUENCING_EXPORT extern const Pitch G7;
    SEQUENCING_EXPORT extern const Pitch GS7;
    SEQUENCING_EXPORT extern const Pitch A7;
    SEQUENCING_EXPORT extern const Pitch AS7;
    SEQUENCING_EXPORT extern const Pitch B7;
    SEQUENCING_EXPORT extern const Pitch C8;
  }

  const int PITCH_COUNT = 89;
  SEQUENCING_EXPORT extern const Pitch Pitches[PITCH_COUNT];
}}
