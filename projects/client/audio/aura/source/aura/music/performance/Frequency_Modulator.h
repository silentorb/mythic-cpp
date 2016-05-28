#pragma once

#include <aura/music/performance/Producer.h>
#include <aura/processors/envelopes/Note_Envelope.h>
#include <aura/processors/Oscillator.h>
#include <aura/music/performance/instruments/Simple_Instrument.h>
#include "dllexport.h"
#include "aura/processors/Loop.h"

namespace aura {

//  class Frequency_Modulation_Stroke : public Stroke {
//      unique_ptr<Oscillator> primary_oscillator;
//      unique_ptr<Oscillator> modulator_oscillator;
//      unique_ptr<Note_Envelope> volume_envelope;
//      float frequency;
//      float modulation_strength;
//
//  public:
//      virtual float update(float beat_delta) override;
//
//      Frequency_Modulation_Stroke(const Note &note, Oscillator *oscillator, Oscillator *modulator_oscillator,
//                                  Note_Envelope *volume_envelope, float modulation_strength) :
//        Stroke(note), primary_oscillator(oscillator), modulator_oscillator(modulator_oscillator),
//        volume_envelope(volume_envelope), frequency(oscillator->get_frequency()),
//        modulation_strength(modulation_strength) { }
//  };

  class MYTHIC_EXPORT Frequency_Modulator_Generator {
      Loop_Function primary_operation;
      Loop_Function modulator_operation;
      Instrumental_Generator modulation_frequency_modifier_generator;
      Instrumental_Generator modulation_strength_generator;

  public:
      Frequency_Modulator_Generator(const Loop_Function &primary_operation, const Loop_Function &modulator_operation,
                                    Instrumental_Generator modulation_frequency_modifier = []() { return 2; },
                                    Instrumental_Generator modulation_strength = []() { return 1000; }) :
        primary_operation(primary_operation),
        modulator_operation(modulator_operation),
        modulation_frequency_modifier_generator(modulation_frequency_modifier),
        modulation_strength(modulation_strength) { }

      Stroke *operator()(const Note &note, Producer &producer, Note_Envelope *volume_envelope);
  };
}