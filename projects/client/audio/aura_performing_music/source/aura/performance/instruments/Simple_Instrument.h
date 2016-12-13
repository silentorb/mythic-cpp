#pragma once

#include <aura/processors/Oscillator.h>
#include <aura/processors/envelopes/Note_Envelope.h>
#include <aura/processors/envelopes/Note_Envelope_Generator.h>
#include "aura/performance/Performance_Producer.h"
#include "aura/performance/Instrument_Old.h"
#include "aura/performance/Musical_Stroke.h"

namespace aura {
  namespace performing {

    typedef std::function<Musical_Stroke *(const sequencing::Note &note, Performance_Producer &producer,
                                           Note_Envelope *volume_envelope)> Instrument_Stroke_Generator;

    class Simple_Instrument : public Instrument_Old {
        Performance_Producer &producer;
        Note_Envelope_Generator &volume_envelope;
//      Loop_Function operation;
        Instrument_Stroke_Generator stroke_generator;

    public:
        Simple_Instrument(Performance_Producer &producer, Loop_Function operation,
                          Note_Envelope_Generator &volume_envelope);
        Simple_Instrument(Performance_Producer &producer, Instrument_Stroke_Generator stroke_generator,
                          Note_Envelope_Generator &volume_envelope);
        virtual ~Simple_Instrument();
        virtual std::unique_ptr<Musical_Stroke> create_sound(const sequencing::Note &note) override;
    };

    class Simple_Instrument_Stroke : public Musical_Stroke {
        unique_ptr<Oscillator> oscillator;
        unique_ptr<Note_Envelope> volume_envelope;

    public:
        virtual float update(float beat_delta) override;

        Simple_Instrument_Stroke(const sequencing::Note &note, Oscillator *oscillator, Note_Envelope *volume_envelope) :
          Musical_Stroke(note), oscillator(oscillator), volume_envelope(volume_envelope) {}

        virtual ~Simple_Instrument_Stroke() {}
    };
  }
}