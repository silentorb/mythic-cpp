#pragma once


#include <foley/Sound.h>

namespace aura {
  namespace performance {
    class Instrument;
  }
}

namespace instrument_foley {

  class Stroke_Sound : public foley::Sound {
      float volume = 1;
      aura::performance::Instrument &instrument;

  public:
      Stroke_Sound(aura::performance::Instrument &instrument) :
        instrument(instrument) {}

      void set_volume(float value) {
        volume = value;
      }

      float get_volume() const {
        return volume;
      }
  };
}