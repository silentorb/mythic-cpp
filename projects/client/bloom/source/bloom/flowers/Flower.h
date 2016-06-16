#pragma once

#include "dllexport.h"
#include "bloom/bloom_export.h"
#include <memory>
#include <vector>

using namespace std;

namespace bloom {
  namespace flowers {
    class BLOOM_EXPORT Flower : no_copy {

    public:
        virtual void update_layout() = 0;
        virtual void update(float delta) = 0;
        virtual void render() = 0;
        virtual Flower *get_parent() const = 0;
    };
  }
}