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
      int offset = -1;

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

      int get_offset() const {
        return offset;
      }

      void set_offset(int offset) {
        Property::offset = offset;
      }

      const Type_Info &get_info() const;

  };
}