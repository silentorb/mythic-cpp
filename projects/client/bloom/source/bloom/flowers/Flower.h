#pragma once

#include "dllexport.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <bloom/layout/Box.h>
#include <bloom/styling/Style.h>
#include "bloom/layout/Bounds.h"
#include "bloom/layout/Measurement.h"
#include "Events.h"

using namespace std;
using namespace glm;

namespace bloom {

  class Border;

  class Fill;

  class Garden;

  class MYTHIC_EXPORT Flower : public Box {

      vector<Listener> listeners;
      vector<unique_ptr<Flower>> children;
      Garden &garden;
      shared_ptr<Style> style;

      // Being a shared variable allows this variable to persist in local variables
      //  after the flower is deleted.
      shared_ptr<bool> is_deleted;

  protected:
      vec2 position;
      bool visible = true;
      Flower *parent = nullptr;

      const Bounds fit_to_children();

  public:
      Flower(Garden &garden, Flower *parent = nullptr);
      Flower(Garden &garden, shared_ptr<Style> &style, Flower *parent = nullptr);

      virtual ~Flower();

      virtual bool emit(Events event);
      virtual const Bounds get_bounds();
      bool point_is_inside(const vec2 &point);
      bool check_activate(const vec2 &point);

      virtual void render();

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

      void remove();

      virtual int get_child_count() const override {
        return children.size();
      }

      virtual Box &get_child_box(int index) const override {
        return *children[index];
      }

      virtual Flower *get_default_focus() const;

      void modal();

      const vector<unique_ptr<Flower>> &get_children() const {
        return children;
      }
  };
}