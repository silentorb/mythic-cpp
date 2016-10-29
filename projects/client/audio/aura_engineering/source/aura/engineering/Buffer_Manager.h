#pragma once

#include "commoner/dllexport.h"
#include <memory>

using namespace std;

namespace aura {
  namespace engineering {

    class MYTHIC_EXPORT Buffer_Manager {
        unique_ptr<unsigned char> data;
        int capacity = 0;
        int size = 0;
        const int element_size;

    public:
        Buffer_Manager(int element_size, int starting_capacity = 0);
        unsigned char *push();
        void pop();
    };
  }
}
