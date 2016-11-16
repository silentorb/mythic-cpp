#pragma once

#include "commoner/dllexport.h"
#include <functional>
#include <glm/vec2.hpp>
#include "bloom/bloom_export.h"

namespace songbird {
  template<typename T>
  class Song;
}

using namespace std;

namespace bloom {

  class Flower_Old;

  namespace flowers {
    class Flower;
  }

  class Event_Id {

  };

  class Event {
      const Event_Id &id;
      const glm::vec2 &point;

  public:
      Event(const Event_Id &id, const glm::vec2 &point) : id(id), point(point) {}

      const Event_Id &get_id() const {
        return id;
      }

      const glm::vec2 &get_point() const {
        return point;
      }
  };

  typedef function<void()> Delegate;
  typedef function<void(const Event &)> Event_Delegate;
  typedef function<void(flowers::Flower *flower)> Flower_Delegate;

  namespace Events {
    extern const Event_Id activate;
    extern const Event_Id drag;
    extern const Event_Id mouse_down;
    extern const Event_Id changed;
    BLOOM_EXPORT extern const Event_Id close;
    BLOOM_EXPORT extern const Event_Id changed_old;
  };
}