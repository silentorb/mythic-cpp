#pragma once

#include "commoner/dllexport.h"
#include "Chord.h"
#include "Time_Signature.h"

namespace aura {
  namespace sequencing {

    class Conductor {
        float tempo = 120;
        float seconds_tempo = tempo / 60;
        Time_Signature time_signature;
        unsigned int sample_rate;

    public:
        Conductor(unsigned int sample_rate) :
          time_signature(4, 4), sample_rate(sample_rate) {}

        float get_tempo() const {
          return tempo;
        }

        float get_seconds_tempo() const {
          return seconds_tempo;
        }

        void set_tempo(float value) {
          tempo = value;
          seconds_tempo = value / 60;
        }

        const Time_Signature &get_time_signature() const {
          return time_signature;
        }

        int get_beats_per_measure() const {
          return time_signature.upper;
        }

        void set_time_signature(const Time_Signature &_time_signature) {
          Conductor::time_signature = _time_signature;
        }

        unsigned int get_sample_rate() const {
          return sample_rate;
        }

        float get_tempo_delta() const {
          return seconds_tempo / sample_rate;
        }
    };
  }
}