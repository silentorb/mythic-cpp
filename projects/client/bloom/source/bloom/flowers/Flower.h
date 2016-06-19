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
        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) {
          return parent_dimensions;
        }

        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) { }

        virtual void update(float delta) { }

        virtual void render() { }

        virtual const Axis_Values &get_absolute_bounds() {
          return parent->get_absolute_bounds();
        }

        virtual bool affects_parent_dimensions() const { return false; }

        virtual bool check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) {
          return false;
        }

        virtual bool get_relative_bounds(glm::vec2 &position, glm::vec2 &dimensions) {
          return false;
        };

        void add_child(Flower *child);

    };

    inline Flower::~Flower() { }
  }
}