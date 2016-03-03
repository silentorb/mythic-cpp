#pragma once

#include <drawing/Element.h>
#include "dllexport.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <bloom/layout/Box.h>
#include "bloom/layout/Bounds.h"
#include "bloom/layout/Measurement.h"
#include "Events.h"

using namespace std;
using namespace glm;

namespace bloom {

  class Border;

  class Fill;

  class Garden;


//  class MYTHIC_EXPORT Abstract_Flower: public Abstract_Box<Abstract_Flower> {
//
//  };

  class MYTHIC_EXPORT Flower : public drawing::Element, public Box {

      enum class Deletion_Mode {
          alive,
          defer_deletion,
          deletion_pending
      };

      vector<Listener> listeners;
      vec2 get_ancestor_offset() const;
      vector<unique_ptr<Flower>> children;
      unique_ptr<Border> border;
      unique_ptr<Fill> fill;
      Garden &garden;

      // Being a shared variable allows this variable to persist in local variables
      //  after the flower is deleted.
      shared_ptr<bool> is_deleted;

  protected:
      vec2 position;
      bool visible = true;
      Flower *parent = nullptr;

      const Bounds fit_to_children();

//      void configure_deleted(bool &deleted) {
//        if (!_deleted) {
//          _deleted =
//        }
//      }
//
//      bool is_deleted() {
//
////        if (deletion == Deletion_Mode::deletion_pending) {
////          parent->remove_child(this);
////          return true;
////        }
////        return false;
//      }

  public:
      Flower(Garden &garden);

      Flower(Garden &garden, Flower &parent);

      virtual ~Flower();

      virtual bool emit(Events event);
      virtual const Bounds get_bounds();
      bool point_is_inside(const vec2 &point);
      bool check_activate(const vec2 &point);

      virtual void render() override;

      void listen(Events event, Flower_Delegate action) {
        listeners.push_back({event, action});
      }

      void click(Flower_Delegate action) {
        listen(Events::activate, action);
      }

      void add_child(Flower *child) {
        child->parent = this;
        children.push_back(unique_ptr<Flower>(child));
      }

      void remove_child(Flower *child);

      void prune() {
        *is_deleted = true;
        parent->remove_child(this);
//        if (deletion == Deletion_Mode::alive) {
//          parent->remove_child(this);
//        }
//        else if (deletion == Deletion_Mode::defer_deletion) {
//          deletion = Deletion_Mode::deletion_pending;
//        }
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

      Flower *get_parent() const {
        return parent;
      }
  };
}