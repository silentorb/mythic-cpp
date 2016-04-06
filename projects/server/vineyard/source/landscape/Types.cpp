#include "Types.h"
#include <string>
#include <vineyard/identity.h>

namespace landscape {
  Type_Info info[] = {
    {"INTEGER", sizeof(int)},
    {"INTEGER", sizeof(vineyard::Identity)},
    {"REAL",    sizeof(float)},
    {"STRING",  sizeof(std::string)},
    {"INTEGER", sizeof(bool)},
    {"INTEGER", sizeof(void*)}
  };

  Type_Info &get_type_info(Types type) {
    return info[static_cast<int>(type)];
  }

}