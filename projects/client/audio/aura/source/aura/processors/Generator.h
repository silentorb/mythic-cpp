#pragma once

#include <functional>
#include <memory>
#include "aura/sequencing/Note.h"

namespace aura {

  typedef std::function<float()> Generator;
//  typedef std::shared_ptr<Generator> Shared_Generator;
  typedef std::function<Generator(const Note &)> Instrumental_Generator;
//  typedef std::shared_ptr<Note_Shared_Generator> Instrumental_Generator;

  MYTHIC_EXPORT Instrumental_Generator Literal(float value);
}