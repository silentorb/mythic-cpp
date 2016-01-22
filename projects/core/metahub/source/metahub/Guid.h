#pragma once

#include <stdint.h>

namespace metahub {

  struct Guid {
      int64_t first;
      int64_t second;

      bool operator<(const Guid &guid) const {
        return first < guid.first || second < guid.second;
      }
  };

  Guid create_guid();
  const Guid GUID_EMPTY = {0, 0};
}

