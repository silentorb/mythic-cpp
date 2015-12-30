#pragma once

#include "dllexport.h"
#include "Mist.h"

namespace lookinglass {
  namespace through {

    template<typename T>
    class MYTHIC_EXPORT Ancient_Mist : public Mist<T> {

    public:
        virtual void initialize(const unsigned int id, const char *name, const std::map<string, Program *> &programs) {

        }

        virtual void update(T *data) {

        }
    };
  }
}