#pragma once

#include "bloom/bloom_export.h"
#include "Flower.h"
#include "Flower_Old.h"

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Wrapper : public Flower_Old {
        unique_ptr<Flower> flower;

    public:
        Wrapper(Flower_Old *parent, Flower *flower) : Flower_Old(parent), flower(flower) { }
    };
  }
}