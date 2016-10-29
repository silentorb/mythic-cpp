#pragma once

#include "foley/Library.h"
#include <vector>

namespace instrument_foley {

  class Instrument_Library : public foley::Library {
//      std::vector<std::unique_ptr<aura::Instrument>> instruments;

  public:
      virtual std::unique_ptr<foley::Sound> get_sound(int id) const override;
  };
}