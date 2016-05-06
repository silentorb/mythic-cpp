#pragma once

#include <aura/music/performance/Stroke.h>
#include <aura/processors/Oscillator.h>
#include "dllexport.h"
#include <memory>
#include <aura/processors/envelopes/Note_Envelope.h>

using namespace std;

namespace aura {

  class Simple_Instrument_Stroke : public Stroke {
      unique_ptr<Oscillator> oscillator;
      unique_ptr<Note_Envelope> volume_envelope;

  public:
      virtual float update(float beat_delta) override;

      Simple_Instrument_Stroke(const Note &note, Oscillator *oscillator, Note_Envelope *volume_envelope) :
        Stroke(note), oscillator(oscillator), volume_envelope(volume_envelope) { }
  };
}