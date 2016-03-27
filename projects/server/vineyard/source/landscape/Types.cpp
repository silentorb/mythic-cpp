#include "Types.h"

namespace landscape {
  Type_Info info[] = {
    {"INTEGER"},
    {"REAL"},
    {"STRING"},
    {"INTEGER"}
  };

  Type_Info &get_type_info(Types type) {
    return info[static_cast<int>(type)];
  }

}