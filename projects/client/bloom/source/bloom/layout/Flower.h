#pragma once

#include <drawing/Element.h>
#include "dllexport.h"
#include <vector>
#include <memory>
#include <functional>
#include <glm/glm.hpp>
#include "Bounds.h"
#include "Measurement.h"

using namespace std;
using namespace glm;

namespace bloom {

  class Flower;

  class Border;

  class Garden;

  enum Flower_Properties {
      width,
      height,
      left,
      top,
      right,
      bottom
  };

  typedef function<void(Flower *flower)> Click_Listener;
  const static int FLOWER_PROPERTY_COUNT = 6;

  class MYTHIC_EXPORT Flower : public drawing::Element, no_copy {
      vector<unique_ptr<Flower>> children;
      Flower *parent = nullptr;
      vector<Click_Listener> on_activate;
      vec2 get_ancestor_offset() const;
//      Measurement properties[FLOWER_PROPERTY_COUNT];

      Measurement width;
      Measurement height;
      Measurement left;
      Measurement top;
      Measurement right;
      Measurement bottom;

      unique_ptr<Border> border;
      Garden &garden;

  protected:
      vec2 position;
      bool visible = true;
      vec2 dimensions = vec2(0);

      inline Measurement* get_properties() {
        return &width;
      }

  public:
      Flower(Garden &garden);

      Flower(Garden &garden, Flower &parent);

      ~Flower();

      virtual bool activate();
      virtual const Bounds get_bounds();
      bool point_is_inside(const vec2 &point);
      bool check_activate(const vec2 &point);

      virtual void render() override;

      void add_activate_listener(Click_Listener listener) {
        on_activate.push_back(listener);
      }

      void add_child(Flower *child) {
        children.push_back(unique_ptr<Flower>(child));
      }

      void remove_child(Flower *child);

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

      void set_border(vec4 color);
      Flower &create_generic_flower();

      void set_width(Measurement &value) {
        width = value;
      }

  };
}