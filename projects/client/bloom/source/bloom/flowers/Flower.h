#pragma once

#include <drawing/Element.h>
#include "dllexport.h"
#include <vector>
#include <memory>
#include <functional>
#include <glm/glm.hpp>
#include <bloom/layout/Box.h>
#include "bloom/layout/Bounds.h"
#include "bloom/layout/Measurement.h"

using namespace std;
using namespace glm;

namespace bloom {

  class Flower;

  class Border;

  class Fill;

  class Garden;

  typedef function<void(Flower *flower)> Click_Listener;

//  class MYTHIC_EXPORT Abstract_Flower: public Abstract_Box<Abstract_Flower> {
//
//  };

  class MYTHIC_EXPORT Flower : public drawing::Element, public Box {
      vector<Click_Listener> on_activate;
      vec2 get_ancestor_offset() const;
      vector<unique_ptr<Flower>> children;
      Flower *parent = nullptr;

      unique_ptr<Border> border;
      unique_ptr<Fill> fill;
      Garden &garden;

  protected:
      vec2 position;
      bool visible = true;
      vec2 dimensions = vec2(0);

      const Bounds fit_to_children();

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

      bool is_visible() const {
        return visible;
      }

      void set_visible(bool visible) {
        Flower::visible = visible;
      }

      void set_border(vec4 color);
      void set_fill(vec4 color);
      Flower &create_generic_flower();

      virtual Box *get_parent_box() const override {
        return parent;
      }

  };
}