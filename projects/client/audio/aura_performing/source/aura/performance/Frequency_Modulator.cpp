#include "Frequency_Modulator.h"

namespace aura {
namespace performing {
  Musical_Stroke *Frequency_Modulator_Generator::operator()(const Note &note, engineering::Engineer &engineer,
                                                            Note_Envelope *volume_envelope) {
      auto oscillator = new Oscillator(engineer, note.get_frequency(), primary_operation);
      auto freq = modulation_frequency(note);
      auto modulator = Oscillator(engineer, freq,
                                  modulator_operation);

      auto frequency = note.get_frequency();
      auto modulation_strength_value = modulation_strength(note);
      oscillator->set_frequency_generator([modulator, frequency, modulation_strength_value]() mutable {
        auto mod = modulator();
        return frequency + mod * modulation_strength_value();
      });
      return new Simple_Instrument_Stroke(note, oscillator, volume_envelope);
  }
}
}