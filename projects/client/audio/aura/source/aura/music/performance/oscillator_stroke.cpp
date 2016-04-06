#include <aura/processors/Oscillator.h>
#include "oscillator_stroke.h"
#include "Lambda_Stroke.h"

namespace aura {
  Stroke *create_oscillator_stroke(Engineer &engineer, const Note &note, Loop_Function operation) {
    Oscillator sine_generator(engineer, note.get_frequency(), operation);
    return new Lambda_Stroke(note, [&, sine_generator](float delta) mutable {
      return sine_generator.update();
    });
  }

}

