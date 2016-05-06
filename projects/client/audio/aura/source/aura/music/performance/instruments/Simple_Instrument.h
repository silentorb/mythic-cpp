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

  class Simple_Instrument_Stroke : public Stroke {
      unique_ptr<Oscillator> oscillator;
      unique_ptr<Note_Envelope> volume_envelope;

  public:
      virtual float update(float beat_delta) override;

      Simple_Instrument_Stroke(const Note &note, Oscillator *oscillator, Note_Envelope *volume_envelope) :
        Stroke(note), oscillator(oscillator), volume_envelope(volume_envelope) { }
  };
}