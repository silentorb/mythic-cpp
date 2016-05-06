#pragma once

#include <aura/processors/Loop.h>
#include "dllexport.h"
#include "Stroke.h"
#include "Producer.h"
#include <aura/sequencing/Note.h>
#include <aura/processors/envelopes/Note_Envelope.h>

namespace aura {

  MYTHIC_EXPORT Stroke *create_oscillator_stroke(Producer & producer, const Note &note,
                                                 Loop_Function operation, Note_Envelope &volume_envelope);

}