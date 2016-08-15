#pragma once

#include "Flower.h"

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Opacity : public flowers::Flower {
        float value;

    public:
        Opacity();
        Opacity(float value);
//        virtual float get_opacity() override;
    };
  }
}