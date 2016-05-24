#include <algorithm>
#include "Flower.h"
#include "bloom/styling/Border.h"
#include "bloom/Garden.h"
#include "bloom/layout/Box_Source.h"
#include "bloom/styling/Fill.h"

namespace bloom {

  Flower::Flower(Flower *parent) : Flower(Garden::get_instance(), parent) { }

  Flower::Flower(Garden &garden, Flower *parent) :
    Flower(garden, garden.get_default_style(), parent) {
  }

  Flower::Flower(Garden &garden, shared_ptr<Style> &style, Flower *parent) :
    garden(garden), parent(parent), style(new Style(style)), Box(garden.get_converter()) {
    if (parent)
      parent->add_child(this);
  }

  Flower::~Flower() {
    if (garden.get_modal() == this)
      garden.pop_modal();
  }

  const Bounds Flower::get_outer_bounds() {
    return Bounds(
      vec2(axis_cache.x.near, axis_cache.y.near),
      vec2(axis_cache.x.length, axis_cache.y.length)
    );
  }

  const Bounds Flower::get_inner_bounds() {
    return Bounds(
      vec2(axis_cache_inner.x.near, axis_cache_inner.y.near),
      vec2(axis_cache_inner.x.length, axis_cache_inner.y.length)
    );
  }

  bool Flower::point_is_inside(const vec2 &point) {
    auto bounds = get_outer_bounds();
    auto top_left = converter.convert_to_pixels(bounds.get_position());
    auto bottom_right = converter.convert_to_pixels(bounds.get_corner());

    auto result = point.x > top_left.x
                  && point.y > top_left.y
                  && point.x < bottom_right.x
                  && point.y < bottom_right.y;

    return result;
  }

  bool Flower::check_activate(const vec2 &point) {
    if (!visible)
      return false;

    for (auto &child: children) {
      if (child->check_activate(point)) {
        return true;
      }
    }

    if (point_is_inside(point)) {
      if (has_listeners(Events::activate)) {
        sing(Events::activate, this);
        return true;
      }
    }

    return false;
  }

  void Flower::render() {
    if (style->get_fill()) {
      auto &bounds = get_outer_bounds();
      style->get_fill()->render(garden.get_draw(), bounds);
    }

    if (style->get_border()) {
      auto &bounds = get_outer_bounds();
      style->get_border()->render(garden.get_draw(), bounds);
    }

    for (auto &child: children) {
      if (child->is_visible()) {
        child->render();
      }
    }
  }

  void Flower::remove_child(Flower *child) {
    int offset = std::find_if(children.begin(), children.end(), [&](unique_ptr<Flower> const &item) {
      return item.get() == child;
    }) - children.begin();

    children.erase(children.begin() + offset);
  }

  void Flower::set_border(vec4 color) {
    if (!style)
      style = shared_ptr<Style>(new Style());

    style->set_border_color(color);
  }

  void Flower::set_fill(vec4 color) {
    if (!style)
      style = shared_ptr<Style>(new Style());

    style->set_fill_color(color);
  }

  void Flower::set_padding(float amount) {
    if (!style)
      style = shared_ptr<Style>(new Style());

    auto value = Simple_Measurement(amount);
    style->set_padding(value);
  }

  Flower &Flower::create_generic_flower() {
    auto flower = new Flower(garden, this);
    return *flower;
  }

  void Flower::remove() {
    parent->remove_child(this);
  }

  void Flower::modal() {
    garden.add_modal(*this);
  }

  Flower *Flower::get_default_focus() const {
    for (auto &child: children) {
      auto result = child->get_default_focus();
      if (result)
        return result;
    }

    return nullptr;
  }

  void Flower::clear() {
    children.clear();
  }

  bool Flower::is_landscape() const {
    return garden.get_orientation() == Orientation::landscape;
  }

  bool Flower::is_portrait() const {
    return garden.get_orientation() == Orientation::portrait;
  }

  void Flower::close() {
    shared_ptr<bool> local_is_deleted = get_is_deleted();
    sing(Events::close, this);
    if (!local_is_deleted)
      remove();
  }

}