#include "Frequency_Modulator.h"

namespace aura {

  Stroke *Frequency_Modulator_Generator::operator()(const Note &note, Producer &producer,
                                                    Note_Envelope *volume_envelope) {
    auto oscillator = new Oscillator(producer.get_engineer(), note.get_frequency(), primary_operation);
    auto modulator = Oscillator(producer.get_engineer(), note.get_frequency() / (*modulation_frequency_modifier_generator)(note),
                                    modulator_operation);
    auto frequency = note.get_frequency();
      auto modulation_strength = (*modulation_strength_generator)(note);
    oscillator->set_frequency_generator([modulator, frequency, modulation_strength]() mutable {
      auto mod = modulator();
      return frequency + mod * modulation_strength();
    });
    return new Simple_Instrument_Stroke(note, oscillator, volume_envelope);
      //    return new Frequency_Modulation_Stroke(note, oscillator, modulator, volume_envelope, modulation_strength);
  }

//  float Frequency_Modulation_Stroke::update(float beat_delta) {
//    progress += beat_delta;
//
//    auto mod = (*modulator_oscillator)();
//    auto modulation_frequency = frequency + mod * modulation_strength;
//
//    primary_oscillator->set_frequency(modulation_frequency);
//    auto value = (*primary_oscillator)();
//
//    return value * volume_envelope->get_value(progress);
//  }
}