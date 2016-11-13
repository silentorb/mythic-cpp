#pragma once

#include "commoner/dllexport.h"
#include "Chord.h"
#include "Time_Signature.h"

namespace aura {
  namespace sequencing {

    class Event_Recorder;

    class Conductor {
        Chord_Instance chord;
        float tempo = 120;
        float seconds_tempo = tempo / 60;
        Time_Signature time_signature;
        Event_Recorder *recorder = nullptr;

    public:
        Conductor(const Chord_Instance &chord) :
          chord(chord), time_signature(4, 4) { }

        Conductor() : Conductor(Chord(Key::C)) { }

        void commence();

        const Chord_Instance &get_chord() const {
          return chord;
        }

        void set_chord(const Chord_Instance chord, float offset = 0, float start = 0, float end = 0);

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

        void set_time_signature(const Time_Signature &_time_signature) {
          Conductor::time_signature = _time_signature;
        }

        Event_Recorder *get_recorder() const {
          return recorder;
        }

        void set_recorder(Event_Recorder *recorder) {
          Conductor::recorder = recorder;
        }
    };
  }
}