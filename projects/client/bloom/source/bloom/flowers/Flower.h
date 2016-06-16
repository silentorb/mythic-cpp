#pragma once

#include "dllexport.h"
#include "bloom/bloom_export.h"
#include <memory>
#include <vector>
#include <bloom/layout/Axis_Value.h>
#include <bloom/layout/Measurement.h>
#include <bloom/layout/Parent_Dimensions.h>

using namespace std;

namespace bloom {
  namespace flowers {
    class BLOOM_EXPORT Flower : no_copy {

    public:
        virtual ~Flower() = 0;
        virtual void update_layout(const Parent_Dimensions &parent_bounds) = 0;
        virtual void update(float delta) = 0;
        virtual void render() = 0;
//        virtual Flower *get_parent() const = 0;
        virtual const Axis_Values &get_absolute_bounds() = 0;
    };

    inline Flower::~Flower() { }
  }
}