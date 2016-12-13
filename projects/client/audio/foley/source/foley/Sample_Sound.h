#pragma once

#include <aura/performing/Sound.h>
#include <vector>
#include <aura/primitives/Decibels.h>

namespace foley {

  template<typename Signal_Type>
  class Sample_Sound : public aura::performing::Sound<Signal_Type> {
      const std::vector<Signal_Type> &buffer;
      unsigned int progress = 0;
      aura::Decibels volume;

  public:
      Sample_Sound(const std::vector<Signal_Type> &buffer, aura::Decibels volume) :
        buffer(buffer), volume(volume) {

      }

      Signal_Type update(float delta) override {
        return buffer[progress++] * volume;
      }

      bool is_finished() const override {
        return progress >= buffer.size();
      }

      aura::Seconds get_duration() const override {
        return 0;
      }
  };
}