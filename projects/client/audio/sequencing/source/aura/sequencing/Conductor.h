#pragma once

#include "dllexport.h"
#include "Chord.h"
#include "Time_Signature.h"

namespace aura {

  class MYTHIC_EXPORT Conductor {
      Chord_Instance chord;
      float tempo = 120;
      Time_Signature time_signature;

  public:

      Conductor(const Chord_Instance &chord) :
        chord(chord), time_signature({4, 4}) { }

      Conductor() : Conductor(Chord(Key::C)) { }

      void commence();

      const Chord_Instance &get_chord() const {
        return chord;
      }

      void set_chord(const Chord_Instance chord) {
        this->chord = chord;
      }

      float get_tempo() const {
        return tempo;
      }

      void set_tempo(float tempo) {
        Conductor::tempo = tempo;
      }

      const Time_Signature &get_time_signature() const {
        return time_signature;
      }

      void set_time_signature(const Time_Signature &_time_signature) {
        Conductor::time_signature = _time_signature;
      }
  };
}