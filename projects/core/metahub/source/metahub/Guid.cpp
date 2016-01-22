#include "Guid.h"

namespace metahub {

  Guid create_guid(){
    static int64_t counter = 1;

    Guid result;
    result.first = 0;
    result.second = counter++;
    return result;
  }

}
