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

      enum class Deletion_Mode {
          alive,
          defer_deletion,
          deletion_pending
      };

      vector<Click_Listener> on_activate;
      vec2 get_ancestor_offset() const;
      vector<unique_ptr<Flower>> children;
      unique_ptr<Border> border;
      unique_ptr<Fill> fill;
      Garden &garden;
      Deletion_Mode deletion = Deletion_Mode::alive;

  protected:
      vec2 position;
      bool visible = true;
      Flower *parent = nullptr;

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

      void click(Click_Listener listener) {
        on_activate.push_back(listener);
      }

      void add_child(Flower *child) {
        child->parent = this;
        children.push_back(unique_ptr<Flower>(child));
      }

      void remove_child(Flower *child);

      void prune() {
        if (deletion == Deletion_Mode::alive) {
          parent->remove_child(this);
        }
        else if (deletion == Deletion_Mode::defer_deletion) {
          deletion = Deletion_Mode::deletion_pending;
        }
      }

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