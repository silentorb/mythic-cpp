#pragma once

#include "dllexport.h"
#include "Types.h"
#include <string>

using namespace std;


namespace landscape {

  class Trellis;

  class MYTHIC_EXPORT Property {
      const string name;
      Trellis *trellis;
      Types type;
      Trellis *other_trellis = nullptr;

  public:
      Property(const string &name, Types type);

      const string &get_name() const {
        return name;
      }

      Trellis &get_trellis() const {
        return *trellis;
      }

      void set_trellis(Trellis &trellis) {
        this->trellis = &trellis;
      }

      Types get_type() const {
        return type;
      }

      Trellis *get_other_trellis() const {
        return other_trellis;
      }
  };
}