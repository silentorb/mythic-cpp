#pragma once

#include "bloom/bloom_export.h"
#include "Flower.h"
#include "Flower_Old.h"

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Wrapper : public Flower_Old {
        unique_ptr<Flower> flower;

    public:
        virtual bool check_event_new(const songbird::Song<Flower_Delegate> &event_type, const vec2 &point) override;

        Wrapper(Flower_Old *parent, Flower *flower) : Flower_Old(parent), flower(flower) { }

        virtual void render() override;
        virtual void update_absolute_dimensions(const Axis_Values_Old &parent_values, const vec2 margin) override;
    };
  }
}