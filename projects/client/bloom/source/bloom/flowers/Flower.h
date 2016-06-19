#pragma once

#include "dllexport.h"
#include "bloom/bloom_export.h"
#include "Events.h"
#include <memory>
#include <vector>
#include <bloom/layout/Axis_Value.h>
#include <bloom/layout/Measurement.h>
#include <bloom/layout/Parent_Dimensions.h>

using namespace std;

namespace bloom {
  namespace flowers {
    class BLOOM_EXPORT Flower : no_copy {
    protected:
        vector<unique_ptr<Flower>> children;
        Flower *parent;

    public:
        Flower(Flower *parent);
        virtual ~Flower() = 0;
        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) = 0;
        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) = 0;
        virtual void update(float delta) = 0;
        virtual void render() = 0;
        virtual const Axis_Values &get_absolute_bounds() = 0;

        virtual bool check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) {
          return false;
        }

        virtual bool get_relative_bounds(Axis_Values &result) {
          return false;
        };

        void add_child(Flower *child);

    };

    inline Flower::~Flower() { }
  }
}