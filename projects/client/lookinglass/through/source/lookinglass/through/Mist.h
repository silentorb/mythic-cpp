#pragma once

#include <vector>
#include "lookinglass/shading/Program.h"

using namespace std;

namespace lookinglass {
  namespace through {

    template<typename T>
    class Mist {
    public:
        virtual void initialize(unsigned int id, char *name, vector<lookinglass::shading::Program> programs) = 0;
        virtual void update(void *data) = 0;
    };
  }
}