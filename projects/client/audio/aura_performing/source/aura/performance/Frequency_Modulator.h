#pragma once

#include <aura/processors/envelopes/Note_Envelope.h>
#include <aura/processors/Oscillator.h>
#include "instruments/Simple_Instrument.h"
#include "aura/processors/Loop.h"

namespace aura {
  namespace performing {
    class Frequency_Modulator_Generator {
        Loop_Function primary_operation;
        Loop_Function modulator_operation;
        Instrumental_Generator modulation_frequency;
        Instrumental_Generator modulation_strength;

    public:
        Frequency_Modulator_Generator(const Loop_Function &primary_operation, const Loop_Function &modulator_operation,
                                      Instrumental_Generator modulation_frequency,
                                      Instrumental_Generator modulation_strength = Literal(1000)) :
          primary_operation(primary_operation),
          modulator_operation(modulator_operation),
          modulation_frequency(modulation_frequency),
          modulation_strength(modulation_strength) {}

        Musical_Stroke *operator()(const Note &note, engineering::Engineer &engineer, Note_Envelope *volume_envelope);
    };
  }
}