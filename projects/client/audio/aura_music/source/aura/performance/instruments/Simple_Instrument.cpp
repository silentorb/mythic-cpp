#include "../Lambda_Stroke.h"
#include "Simple_Instrument.h"

namespace aura {

  class Default_Generator {
      Loop_Function operation;

  public:
      Default_Generator(Loop_Function operation) :
        operation(operation) {}

      Musical_Stroke *operator()(const Note &note, Producer &producer, Note_Envelope *volume_envelope) {
        auto oscillator = new Oscillator(producer.get_engineer(), note.get_frequency(), operation);
        return new Simple_Instrument_Stroke(note, oscillator, volume_envelope);
      }
  };

  Simple_Instrument::Simple_Instrument(Producer &producer, Loop_Function operation,
                                       Note_Envelope_Generator &volume_envelope) :
    producer(producer), volume_envelope(volume_envelope) {

    stroke_generator = Default_Generator(operation);
  }

  Simple_Instrument::Simple_Instrument(Producer &producer, Instrument_Stroke_Generator stroke_generator,
                                       Note_Envelope_Generator &volume_envelope) :
    producer(producer), volume_envelope(volume_envelope), stroke_generator(stroke_generator) {

  }

  Musical_Stroke *Simple_Instrument::generate_stroke(const Note &note) {
    return stroke_generator(note, producer, volume_envelope.generate_envelope());
  }

  float Simple_Instrument_Stroke::update(float beat_delta) {
    progress += beat_delta;
    auto value = (*oscillator)();
    return value * volume_envelope->get_value(progress);
  }

}