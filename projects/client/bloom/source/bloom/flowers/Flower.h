#pragma once

#include <drawing/Element.h>
#include "dllexport.h"
#include <vector>
#include <memory>
#include <functional>
#include <glm/glm.hpp>
#include "bloom/Bounds.h"

using namespace std;
using namespace glm;

namespace bloom {

  class Flower;

  typedef function<void(Flower *flower)> Click_Listener;

  class MYTHIC_EXPORT Flower : public drawing::Element, no_copy {
      vector<unique_ptr<Flower>> children;
      Flower *parent = nullptr;
      vector<Click_Listener> on_activate;
      vec2 get_ancestor_offset() const;

  protected:
      vec2 position;
      bool visible;
      vec2 dimensions = vec2(0);

  public:
      Flower() { }

      Flower(Flower &parent);

      virtual bool activate();
      virtual const Bounds get_bounds();
      bool point_is_inside(const vec2 &point);
      bool check_activate(const vec2 &point);

      virtual void render() override;

      void add_activate_listener(Click_Listener listener) {
        on_activate.push_back(listener);
      }

      void add(Flower *child) {
        children.push_back(unique_ptr<Flower>(child));
      }

      void remove(Flower *child);

      const vec2 &get_position() const {
        return position;
      }

      const vec2 get_absolute_position() const;

      void set_position(const vec2 &position) {
        Flower::position = position;
      }

      bool is_visible() const {
        return visible;
      }

      void set_visible(bool visible) {
        Flower::visible = visible;
      }
  };
}