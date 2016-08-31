#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <bloom/layout/Box_Old.h>
#include <bloom/styling/Style.h>
#include <songbird/Singer.h>
#include "bloom/layout/Bounds.h"
#include "bloom/layout/Measurement.h"
#include "bloom/flowers/Events.h"

using namespace std;
using namespace glm;

namespace bloom {

  class Border;

  class Fill;

  class Garden;

  enum class Orientation {
      portrait,
      landscape
  };

  class BLOOM_EXPORT Flower_Old : public Box_Old, public songbird::Singer {
      vector<unique_ptr<Flower_Old>> children;
      shared_ptr<Style> style;

  protected:
      Garden &garden;
      vec2 position;
      bool visible = true;
      Flower_Old *parent = nullptr;

      virtual bool clips_children() override;

      virtual void modify_inner() override { }

  public:
      Flower_Old(Flower_Old *parent = nullptr);
      Flower_Old(Garden &garden, Flower_Old *parent = nullptr);
      Flower_Old(Garden &garden, shared_ptr<Style> &style, Flower_Old *parent = nullptr);

      virtual ~Flower_Old();

//      virtual bool emit(Events event);
      virtual const Bounds get_outer_bounds();
      virtual const Bounds get_inner_bounds();
      bool point_is_inside(const vec2 &point);
//      virtual bool check_event(const songbird::Song<Flower_Delegate_Old> &event_type, const vec2 &point);
      virtual bool check_event_new(const songbird::Song<Flower_Delegate> &event_type, const vec2 &point);

      virtual void render();
      virtual void update(float delta);
//      void listen(Events event, Flower_Delegate action) {
//        listeners.push_back({event, action});
//      }

//      void click(Flower_Delegate_Old action) {
//        listen(Events::activate_old, action);
//      }

      void add_child(Flower_Old *child) {
        child->parent = this;
        children.push_back(unique_ptr<Flower_Old>(child));
      }

      void remove_child(Flower_Old *child);

      void prune() {
        parent->remove_child(this);
      }

      bool is_visible() const {
        return visible;
      }

      void set_visible(bool visible) {
        Flower_Old::visible = visible;
      }

      void set_border(vec4 color);
      void set_fill(vec4 color);
      void set_padding(float amount);
      void set_padding(float horizontal, float vertical);
      Flower_Old &create_generic_flower();

      virtual Box_Old *get_parent_box() const override {
        return parent;
      }

      Flower_Old *get_parent() const {
        return parent;
      }

      void remove();

      virtual int get_child_count() const override {
        return children.size();
      }

      virtual Box_Old &get_child_box(int index) const override {
        return *children[index];
      }

      virtual Flower_Old *get_default_focus() const;

      void modal();

      const vector<unique_ptr<Flower_Old>> &get_children() const {
        return children;
      }

      void clear();

      bool is_landscape() const;
      bool is_portrait() const;

      const Vector4 *get_padding() const {
        return style->get_padding();
      }

      virtual void close();

      virtual Box_Style &get_box_style() override {
        return *style;
      }

      shared_ptr<Style> &get_style() {
        return style;
      }

  };
}