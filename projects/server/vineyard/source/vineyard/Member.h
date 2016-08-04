#pragma once

#include <landscape/Property.h>
#include "vineyard/vineyard_export.h"
#include "Seed.h"
#include "landscape/Trellis.h"

namespace vineyard {

  template<typename T>
  class Member {
      Seed *seed;
      const landscape::Property *property;

  public:
      Member(Seed *seed, const landscape::Property *property) : seed(seed), property(property) {}

      Member(Seed &seed, int index) : seed(&seed), property(&seed.get_trellis().get_property(index)) {}

      T get_value() {
        return *(T *) ((char *) seed + property->get_offset());
      }

      void set_value(T value) {
        *(T *) ((char *) seed + property->get_offset()) = value;
        seed->save_property(*property);
      }
  };
}