#pragma once

#include "bloom/bloom_export.h"
#include "Events.h"
#include <memory>
#include <vector>
#include <bloom/layout/Axis_Value.h>
#include <bloom/layout/Measurement.h>
#include <bloom/layout/Parent_Dimensions.h>
#include <commoner/debug-macro.h>

using namespace std;

namespace bloom {
  namespace flowers {

    class Parent;

    class BLOOM_EXPORT Flower {

    public:
        Flower();
        virtual ~Flower() = 0;

//#ifdef COMMON_DEBUG
//#endif

        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) = 0;
        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) = 0;
        virtual void update(float delta)= 0;
        virtual void render() = 0;
        virtual const Axis_Values &get_absolute_bounds() const = 0;
        virtual bool affects_parent_dimensions() const = 0;
        virtual bool check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) = 0;
        virtual bool get_relative_bounds(glm::vec2 &position, glm::vec2 &dimensions) = 0;
        virtual void remove() = 0;
        virtual Flower *get_parent() const = 0;
        virtual void set_parent(Parent *parent) = 0;
    };

    inline Flower::~Flower() {}
  }
}