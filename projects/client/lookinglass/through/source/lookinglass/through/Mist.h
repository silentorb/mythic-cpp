#pragma once

#include "dllexport.h"

#include <map>
#include "lookinglass/shading/Program.h"

using namespace std;

namespace lookinglass {
  using namespace shading;

    namespace through {

      template<typename T>
      class MYTHIC_EXPORT Mist {
      public:
          virtual void initialize(const unsigned int id, const char *name, const std::map<string, Program *> &programs) = 0;
          virtual void update(T *data) = 0;
      };

      }
}