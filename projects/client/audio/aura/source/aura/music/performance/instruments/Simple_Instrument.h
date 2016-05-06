#pragma once

#include <aura/music/performance/Producer.h>
#include <aura/processors/Oscillator.h>
#include <aura/processors/envelopes/Note_Envelope.h>
#include <aura/processors/envelopes/Note_Envelope_Generator.h>
#include "dllexport.h"
#include "Instrument.h"

namespace aura {

  class MYTHIC_EXPORT Simple_Instrument : public Instrument {
      Producer & producer;
      const Note &note;
      Note_Envelope_Generator &volume_envelope;
      Loop_Function operation;

  public:
      Simple_Instrument(Producer &producer, Loop_Function operation, Note_Envelope_Generator &volume_envelope);

      virtual Stroke *generate_stroke(const Note &note) override;
  };
}