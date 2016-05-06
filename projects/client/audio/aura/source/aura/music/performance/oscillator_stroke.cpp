#include <aura/processors/Oscillator.h>
#include "oscillator_stroke.h"
#include "Lambda_Stroke.h"

namespace aura {
//  Stroke *create_oscillator_stroke(Producer &producer, const Note &note,
//                                   Loop_Function operation, Note_Envelope &volume_envelope) {
//    Oscillator sine_generator(producer.get_engineer(), note.get_frequency(), operation);
//    double position = 0;
//    return new Lambda_Stroke(note, [=, &volume_envelope, &producer](float delta) mutable {
//      position += producer.get_conductor().get_seconds_tempo() * delta;
//      auto value = sine_generator.update();
//      return value * volume_envelope.get_value(position);
//    });
//  }

}

