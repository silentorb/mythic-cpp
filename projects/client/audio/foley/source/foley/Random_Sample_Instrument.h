#pragma once

#include <aura/performing/Instrument.h>
#include <vector>
#include <randomly/Dice.h>
#include "Sample_Sound.h"

namespace foley {

  template<typename Signal_Type, typename Event_Type>
  class Random_Sample_Instrument :
    public aura::performing::Instrument<aura::performing::Sound<Signal_Type>, Event_Type> {
      std::vector<std::vector<Signal_Type>> buffers;
      int last_sound = -1;
      randomly::Dice &dice;

  public:
      Random_Sample_Instrument(randomly::Dice &dice) : dice(dice) {
      }

      virtual std::unique_ptr<aura::performing::Sound<Signal_Type>> create_sound(const Event_Type &event) {
        auto next = dice.get_int(buffers.size() - 1);
        if (next == last_sound)
          next = (next + 1) % buffers.size();

        last_sound = next;
        return std::unique_ptr<Sample_Sound<Signal_Type>>(new Sample_Sound<Signal_Type>(buffers[next], event.get_volume()));
      }

      virtual ~Random_Sample_Instrument() {}

      template<typename Sound_Type>
      Random_Sample_Instrument *prepare(aura::performing::Instrument<Sound_Type, Event_Type> &instrument,
                                        const Event_Type &event, size_t count, unsigned int sample_rate) {
        const float delta = 1.0f / sample_rate;
        buffers.resize(count);
        for (int i = 0; i < count; ++i) {
          auto &buffer = buffers[i];
          auto sound = instrument.create_sound(event);
          if (sound->get_duration() <= 0)
            throw std::runtime_error("Cannot pre-record sound with a duration of 0 or less.");

          unsigned int duration = std::ceil(sound->get_duration() * sample_rate);

          buffer.resize(duration);
          for (int j = 0; j < duration; ++j) {
            buffer[j] = sound->update(delta);
          }
        }

        return this;
      }
  };
}