#pragma once

#include <functional>
#include <memory>
#include "aura/sequencing/Note.h"

namespace aura {

  typedef std::function<float()> Generator;
  typedef std::shared_ptr<Generator> Shared_Generator;
  typedef std::function<Shared_Generator(const Note&)> Note_Shared_Generator;
  typedef std::shared_ptr<Note_Shared_Generator> Instrumental_Generator;

  Instrumental_Generator
}