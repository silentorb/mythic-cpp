#pragma once

#include <aura/music/sequencing/Key.h>
#include "dllexport.h"

namespace aura {

  struct Pitch {
      int index;
      float frequency;
      const char *name;
      Key key;
  };

  namespace pitches {
    const Pitch GSN1 = {0, 25.957, "GS-1", Key::G};
    const Pitch A0 = {1, 27.500, "A0", Key::A};
    const Pitch AS0 = {2, 29.135, "A#0", Key::A};
    const Pitch B0 = {3, 30.868, "B0", Key::B};
    const Pitch C1 = {4, 32.703, "C1", Key::C};
    const Pitch CS1 = {5, 34.648, "C#1", Key::C};
    const Pitch D1 = {6, 36.708, "D1", Key::D};
    const Pitch DS1 = {7, 38.890, "D#1", Key::D};
    const Pitch E1 = {8, 41.203, "E1", Key::E};
    const Pitch F1 = {9, 43.654, "F1", Key::F};
    const Pitch FS1 = {10, 46.249, "F#1", Key::F};
    const Pitch G1 = {11, 48.999, "G1", Key::G};
    const Pitch GS1 = {12, 51.913, "G#1", Key::G};
    const Pitch A1 = {13, 55.00, "A1", Key::A};
    const Pitch AS1 = {14, 58.271, "A#1", Key::A};
    const Pitch B1 = {15, 61.735, "B1", Key::B};
    const Pitch C2 = {16, 65.406, "C2", Key::C};
    const Pitch CS2 = {17, 69.296, "C#2", Key::C};
    const Pitch D2 = {18, 73.416, "D2", Key::D};
    const Pitch DS2 = {19, 77.782, "D#2", Key::D};
    const Pitch E2 = {20, 82.407, "E2", Key::E};
    const Pitch F2 = {21, 87.307, "F2", Key::F};
    const Pitch FS2 = {22, 92.499, "F#2", Key::F};
    const Pitch G2 = {23, 97.999, "G2", Key::G};
    const Pitch GS2 = {24, 103.82, "G#2", Key::G};
    const Pitch A2 = {25, 110.00, "A2", Key::A};
    const Pitch AS2 = {26, 116.54, "A#2", Key::A};
    const Pitch B2 = {27, 123.47, "B2", Key::B};
    const Pitch C3 = {28, 130.81, "C3", Key::C};
    const Pitch CS3 = {29, 138.59, "C#3", Key::C};
    const Pitch D3 = {30, 146.83, "D3", Key::D};
    const Pitch DS3 = {31, 155.56, "D#3", Key::D};
    const Pitch E3 = {32, 164.81, "E3", Key::E};
    const Pitch F3 = {33, 174.61, "F3", Key::F};
    const Pitch FS3 = {34, 185.00, "F#3", Key::F};
    const Pitch G3 = {35, 196.00, "G3", Key::G};
    const Pitch GS3 = {36, 207.65, "G#3", Key::G};
    const Pitch A3 = {37, 220.00, "A3", Key::A};
    const Pitch AS3 = {38, 233.08, "A#3", Key::A};
    const Pitch B3 = {39, 246.94, "B3", Key::B};
    const Pitch C4 = {40, 261.63, "C4", Key::C};
    const Pitch CS4 = {41, 277.18, "C#4", Key::C};
    const Pitch D4 = {42, 293.66, "D4", Key::D};
    const Pitch DS4 = {43, 311.13, "D#4", Key::D};
    const Pitch E4 = {44, 329.63, "E4", Key::E};
    const Pitch F4 = {45, 349.23, "F4", Key::F};
    const Pitch FS4 = {46, 369.99, "F#4", Key::F};
    const Pitch G4 = {47, 392.00, "G4", Key::G};
    const Pitch GS4 = {48, 415.30, "G#4", Key::G};
    const Pitch A4 = {49, 440.00, "A4", Key::A};
    const Pitch AS4 = {50, 466.16, "A#4", Key::A};
    const Pitch B4 = {51, 493.88, "B4", Key::B};
    const Pitch C5 = {52, 523.25, "C5", Key::C};
    const Pitch CS5 = {53, 554.37, "C#5", Key::C};
    const Pitch D5 = {54, 587.33, "D5", Key::D};
    const Pitch DS5 = {55, 622.25, "D#5", Key::D};
    const Pitch E5 = {56, 659.26, "E5", Key::E};
    const Pitch F5 = {57, 698.46, "F5", Key::F};
    const Pitch FS5 = {58, 739.99, "F#5", Key::F};
    const Pitch G5 = {59, 783.99, "G5", Key::G};
    const Pitch GS5 = {60, 830.61, "G#5", Key::G};
    const Pitch A5 = {61, 880.00, "A5", Key::A};
    const Pitch AS5 = {62, 932.33, "A#5", Key::A};
    const Pitch B5 = {63, 987.77, "B5", Key::B};
    const Pitch C6 = {64, 1046.5, "C6", Key::C};
    const Pitch CS6 = {65, 1108.7, "C#6", Key::C};
    const Pitch D6 = {66, 1174.7, "D6", Key::D};
    const Pitch DS6 = {67, 1244.5, "D#6", Key::D};
    const Pitch E6 = {68, 1318.5, "E6", Key::E};
    const Pitch F6 = {69, 1396.9, "F6", Key::F};
    const Pitch FS6 = {70, 1480.0, "F#6", Key::F};
    const Pitch G6 = {71, 1568.0, "G6", Key::G};
    const Pitch GS6 = {72, 1661.2, "G#6", Key::G};
    const Pitch A6 = {73, 1760.0, "A6", Key::A};
    const Pitch AS6 = {74, 1864.6, "A#6", Key::A};
    const Pitch B6 = {75, 1975.5, "B6", Key::B};
    const Pitch C7 = {76, 2093.0, "C7", Key::C};
    const Pitch CS7 = {77, 2217.5, "C#7", Key::C};
    const Pitch D7 = {78, 2349.3, "D7", Key::D};
    const Pitch DS7 = {79, 2489.0, "D#7", Key::D};
    const Pitch E7 = {80, 2637.0, "E7", Key::E};
    const Pitch F7 = {81, 2793.8, "F7", Key::F};
    const Pitch FS7 = {82, 2959.9, "F#7", Key::F};
    const Pitch G7 = {83, 3136.0, "G7", Key::G};
    const Pitch GS7 = {84, 3322.4, "G#7", Key::G};
    const Pitch A7 = {85, 3520.0, "A7", Key::A};
    const Pitch AS7 = {86, 3729.3, "A#7", Key::A};
    const Pitch B7 = {87, 3951.1, "B7", Key::B};
    const Pitch C8 = {88, 4186.0, "C8", Key::C};
  }

  const int PITCH_COUNT = 89;
  const Pitch Pitches[PITCH_COUNT] = {
    pitches::GSN1,
    pitches::A0,
    pitches::AS0,
    pitches::B0,
    pitches::C1,
    pitches::CS1,
    pitches::D1,
    pitches::DS1,
    pitches::E1,
    pitches::F1,
    pitches::FS1,
    pitches::G1,
    pitches::GS1,
    pitches::A1,
    pitches::AS1,
    pitches::B1,
    pitches::C2,
    pitches::CS2,
    pitches::D2,
    pitches::DS2,
    pitches::E2,
    pitches::F2,
    pitches::FS2,
    pitches::G2,
    pitches::GS2,
    pitches::A2,
    pitches::AS2,
    pitches::B2,
    pitches::C3,
    pitches::CS3,
    pitches::D3,
    pitches::DS3,
    pitches::E3,
    pitches::F3,
    pitches::FS3,
    pitches::G3,
    pitches::GS3,
    pitches::A3,
    pitches::AS3,
    pitches::B3,
    pitches::C4,
    pitches::CS4,
    pitches::D4,
    pitches::DS4,
    pitches::E4,
    pitches::F4,
    pitches::FS4,
    pitches::G4,
    pitches::GS4,
    pitches::A4,
    pitches::AS4,
    pitches::B4,
    pitches::C5,
    pitches::CS5,
    pitches::D5,
    pitches::DS5,
    pitches::E5,
    pitches::F5,
    pitches::FS5,
    pitches::G5,
    pitches::GS5,
    pitches::A5,
    pitches::AS5,
    pitches::B5,
    pitches::C6,
    pitches::CS6,
    pitches::D6,
    pitches::DS6,
    pitches::E6,
    pitches::F6,
    pitches::FS6,
    pitches::G6,
    pitches::GS6,
    pitches::A6,
    pitches::AS6,
    pitches::B6,
    pitches::C7,
    pitches::CS7,
    pitches::D7,
    pitches::DS7,
    pitches::E7,
    pitches::F7,
    pitches::FS7,
    pitches::G7,
    pitches::GS7,
    pitches::A7,
    pitches::AS7,
    pitches::B7,
    pitches::C8,
  };
}
