#pragma once

#include <aura/processors/Loop.h>
#include "dllexport.h"
#include "Stroke.h"
#include <aura/sequencing/Note.h>

namespace aura {

  MYTHIC_EXPORT Stroke *create_oscillator_stroke(Engineer &engineer, const Note &note, Loop_Function operation);

}