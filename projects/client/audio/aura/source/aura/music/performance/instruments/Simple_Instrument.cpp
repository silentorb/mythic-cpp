#include <aura/music/performance/Lambda_Stroke.h>
#include "Simple_Instrument.h"
#include "Simple_Instrument_Stroke.h"

namespace aura {
  Simple_Instrument::Simple_Instrument(Producer &producer, Loop_Function operation,
                                       Note_Envelope_Generator &volume_envelope) :
    producer(producer), note(note),
    volume_envelope(volume_envelope),
    operation(operation) {

  }

  Stroke *Simple_Instrument::generate_stroke(const Note &note) {
    auto oscillator = new Oscillator(producer.get_engineer(), note.get_frequency(), operation);
    return new Simple_Instrument_Stroke(note, oscillator, volume_envelope.generate_envelope());
  }
}