#pragma once

#include <aura/processors/Loop.h>
#include "dllexport.h"
#include "Stroke.h"
#include <aura/music/sequencing/Note.h>

namespace aura {

  Stroke* create_oscillator_stroke(Engineer &engineer, const Note & note, Loop_Function operation);

}