#pragma once

#include "../Producer.h"
#include <aura/processors/Oscillator.h>
#include <aura/processors/envelopes/Note_Envelope.h>
#include <aura/processors/envelopes/Note_Envelope_Generator.h>
#include "commoner/dllexport.h"
#include "../Instrument.h"

namespace aura {
  typedef std::function<Musical_Stroke *(const Note &note, Producer &producer, Note_Envelope *volume_envelope)> Instrument_Stroke_Generator;

  class MYTHIC_EXPORT Simple_Instrument : public Instrument {
      Producer &producer;
      Note_Envelope_Generator &volume_envelope;
//      Loop_Function operation;
      Instrument_Stroke_Generator stroke_generator;

  public:
      Simple_Instrument(Producer &producer, Loop_Function operation, Note_Envelope_Generator &volume_envelope);
      Simple_Instrument(Producer &producer, Instrument_Stroke_Generator stroke_generator,
                        Note_Envelope_Generator &volume_envelope);

      virtual Musical_Stroke *generate_stroke(const Note &note) override;
  };

  class Simple_Instrument_Stroke : public Musical_Stroke {
      unique_ptr<Oscillator> oscillator;
      unique_ptr<Note_Envelope> volume_envelope;

  public:
      virtual float update(float beat_delta) override;

      Simple_Instrument_Stroke(const Note &note, Oscillator *oscillator, Note_Envelope *volume_envelope) :
        Musical_Stroke(note), oscillator(oscillator), volume_envelope(volume_envelope) { }

      virtual ~Simple_Instrument_Stroke() { }
  };
}