#include <algorithm>
#include "Flower.h"
#include "bloom/styling/Border.h"
#include "bloom/Garden.h"
#include "bloom/layout/Box_Source.h"
#include "bloom/styling/Fill.h"

namespace bloom {

  Flower::Flower(Garden &garden) : garden(garden), Box(garden.get_converter()), is_deleted(new bool(false)) { }

  Flower::Flower(Garden &garden, Flower &parent) : garden(garden), Box(garden.get_converter()), is_deleted(new bool(false)) {
    parent.add_child(this);
  }

  Flower::~Flower() { }

  bool Flower::emit(Events event) {
    bool has_events = false;
    shared_ptr<bool> local_is_deleted = is_deleted;
    for (auto &listener: listeners) {
      if (listener.type == event) {
        has_events = true;

        listener.action(this);
        if (local_is_deleted)
          return true;
      }
    }

    return has_events;
  }

  const Bounds Flower::fit_to_children() {
    throw runtime_error("Not implemented.");
//    if (children.size() == 0)
//      return Bounds(0, 0, 0, 0);
//
//    if (children.size() == 1)
//      return children[0]->get_bounds();
//
//    float top, left, bottom, right;
//    if (dimensions.x == 0 || dimensions.y) {
//      top = 10000;
//      left = 10000;
//      bottom = 0;
//      right = 0;
//    }
//    else {
//      auto absolute_position = get_absolute_position();
//      top = absolute_position.y;
//      left = absolute_position.x;
//      right = absolute_position.x + dimensions.x;
//      bottom = absolute_position.y + dimensions.y;
//    }
//
//    for (auto &child: children) {
//      auto &bounds = child->get_bounds();
//      if (bounds.bottom_right.x < left)
//        left = bounds.bottom_right.x;
//
//      if (bounds.bottom_right.y < top)
//        top = bounds.bottom_right.y;
//
//      if (bounds.bottom_right.x > right)
//        right = bounds.bottom_right.x;
//
//      if (bounds.bottom_right.y > bottom)
//        bottom = bounds.bottom_right.y;
//    }
//
//    return Bounds(top, left, bottom, right);
  }

  const Bounds Flower::get_bounds() {
    return Bounds(
      vec2(axis_cache.x.near, axis_cache.y.near),
      vec2(axis_cache.x.length, axis_cache.y.length)
    );
  }

  bool Flower::point_is_inside(const vec2 &point) {
    auto bounds = get_bounds();
    auto top_left = converter.convert(bounds.get_position());
    auto bottom_right = converter.convert(bounds.get_corner());

    auto result = point.x > top_left.x
                  && point.y > top_left.y
                  && point.x < bottom_right.x
                  && point.y < bottom_right.y;

    return result;
  }

  bool Flower::check_activate(const vec2 &point) {
    for (auto &child: children) {
      if (child->check_activate(point)) {
        return true;
      }
    }

    if (point_is_inside(point)) {
      return emit(Events::activate);
    }

    return false;
  }

  void Flower::render() {
    if (fill.get() != nullptr) {
      auto &bounds = get_bounds();
      fill->render(garden.get_draw(), bounds);
    }

    if (border.get() != nullptr) {
      auto &bounds = get_bounds();
      border->render(garden.get_draw(), bounds);
    }

    for (auto &child: children) {
      if (child->is_visible()) {
        child->render();
      }
    }
  }

  vec2 Flower::get_ancestor_offset() const {
    if (parent == nullptr)
      return vec2(0);

    return parent->get_absolute_position();
  }

  void Flower::remove_child(Flower *child) {
    int offset = std::find_if(children.begin(), children.end(), [&](unique_ptr<Flower> const &item) {
      return item.get() == child;
    }) - children.begin();

    children.erase(children.begin() + offset);
  }

  void Flower::set_border(vec4 color) {
    if (border.get() == nullptr) {
      border = unique_ptr<Border>(new Border());
    }

    border->set_color(color);
  }

  void Flower::set_fill(vec4 color) {
    if (fill.get() == nullptr) {
      fill = unique_ptr<Fill>(new Fill());
    }

    fill->set_color(color);
  }

  Flower &Flower::create_generic_flower() {
    auto flower = new Flower(garden, *this);
    return *flower;
  }

  void Flower::remove() {
    parent->remove_child(this);
  }
}