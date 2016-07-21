#include <algorithm>
#include "Flower_Old.h"
#include "bloom/styling/Border.h"
#include "bloom/Garden.h"
#include "bloom/layout/Box_Source.h"
#include "bloom/styling/Fill.h"

namespace bloom {

  Flower_Old::Flower_Old(Flower_Old *parent) : Flower_Old(Garden::get_instance(), parent) { }

  Flower_Old::Flower_Old(Garden &garden, Flower_Old *parent) :
    Flower_Old(garden, garden.get_default_style(), parent) {
  }

  Flower_Old::Flower_Old(Garden &garden, shared_ptr<Style> &style, Flower_Old *parent) :
    garden(garden), parent(parent), style(new Style(style)), Box_Old(garden.get_converter()) {
    if (parent)
      parent->add_child(this);
  }

  Flower_Old::~Flower_Old() {
    if (garden.get_modal() == this)
      garden.pop_modal();
  }

  const Bounds Flower_Old::get_outer_bounds() {
    return Bounds(
      vec2(axis_cache.x.near, axis_cache.y.near),
      vec2(axis_cache.x.length, axis_cache.y.length)
    );
  }

  const Bounds Flower_Old::get_inner_bounds() {
    return Bounds(
      vec2(axis_cache_inner.x.near, axis_cache_inner.y.near),
      vec2(axis_cache_inner.x.length, axis_cache_inner.y.length)
    );
  }

  bool Flower_Old::point_is_inside(const vec2 &point) {
    Bounds bounds = get_outer_bounds();
    vec2 corner_offset;

    if (clip_bounds.get()) {
      if (clip_bounds->y.absolute_far < bounds.get_corner().y)
        corner_offset.y = clip_bounds->y.absolute_far - bounds.get_corner().y;
    }
    auto top_left = converter.convert_to_pixels(bounds.get_position());
    auto bottom_right = converter.convert_to_pixels(bounds.get_corner() + corner_offset);

    auto result = point.x > top_left.x
                  && point.y > top_left.y
                  && point.x < bottom_right.x
                  && point.y < bottom_right.y;

    return result;
  }

  bool Flower_Old::check_event(const songbird::Song<Flower_Delegate_Old> &event_type, const vec2 &point) {
    if (!visible)
      return false;

    for (auto &child: children) {
      if (child->check_event(event_type, point)) {
        return true;
      }
    }

    if (point_is_inside(point)) {
      if (has_listeners(event_type)) {
        sing(event_type, this);
        return true;
      }
    }

    return false;
  }

  bool Flower_Old::check_event_new(const songbird::Song<Flower_Delegate> &event_type, const vec2 &point) {
    if (!visible)
      return false;

    for (auto &child: children) {
      if (child->check_event_new(event_type, point)) {
        return true;
      }
    }

    return false;
  }

  void Flower_Old::render() {
    if (style->get_fill()) {
      auto &bounds = get_outer_bounds();
      style->get_fill()->render(garden.get_draw(), bounds);
    }

    // This functionality does not currently support having hidden overflow children inside hidden overflow parents.
    // I can add it later when the need arises.
    bool overflow_is_hidden = false;
    if (style.get() && style->get_overflow() == Overflow::hidden) {
      overflow_is_hidden = true;
      auto &bounds = get_outer_bounds();
      auto position = converter.convert_to_pixels(bounds.get_position());
      auto dimensions = converter.convert_to_pixels(bounds.get_dimensions());
      garden.get_draw().enable_scissor_box(position.x, converter.get_pixel_dimensions().y - position.y - dimensions.y,
                                           dimensions.x, dimensions.y
      );
    }

    for (auto &child: children) {
      if (child->is_visible()) {
        child->render();
      }
    }

    if (overflow_is_hidden) {
      garden.get_draw().disable_scissor_box();
    }

    if (style->get_border()) {
      auto &bounds = get_outer_bounds();
      style->get_border()->render(garden.get_draw(), bounds);
    }
  }

  void Flower_Old::remove_child(Flower_Old *child) {
    int offset = std::find_if(children.begin(), children.end(), [&](unique_ptr<Flower_Old> const &item) {
      return item.get() == child;
    }) - children.begin();

    children.erase(children.begin() + offset);
  }

  void Flower_Old::set_border(vec4 color) {
    if (!style)
      style = shared_ptr<Style>(new Style());

    style->set_border_color(color);
  }

  void Flower_Old::set_fill(vec4 color) {
    if (!style)
      style = shared_ptr<Style>(new Style());

    style->set_fill_color(color);
  }

  void Flower_Old::set_padding(float amount) {
    if (!style)
      style = shared_ptr<Style>(new Style());

    auto value = Measurement(amount);
    style->set_padding(value);
  }

  void Flower_Old::set_padding(float horizontal, float vertical) {
    if (!style)
      style = shared_ptr<Style>(new Style());

    auto horizontal_measurement = Measurement(horizontal);
    auto vertical_measurement = Measurement(vertical);
    style->set_padding(horizontal_measurement, vertical_measurement);
  }

  Flower_Old &Flower_Old::create_generic_flower() {
    auto flower = new Flower_Old(garden, this);
    return *flower;
  }

  void Flower_Old::remove() {
    parent->remove_child(this);
  }

  void Flower_Old::modal() {
    garden.add_modal(*this);
  }

  Flower_Old *Flower_Old::get_default_focus() const {
    for (auto &child: children) {
      auto result = child->get_default_focus();
      if (result)
        return result;
    }

    return nullptr;
  }

  void Flower_Old::clear() {
    children.clear();
  }

  bool Flower_Old::is_landscape() const {
    return garden.get_orientation() == Orientation::landscape;
  }

  bool Flower_Old::is_portrait() const {
    return garden.get_orientation() == Orientation::portrait;
  }

  void Flower_Old::close() {
    shared_ptr<bool> local_is_deleted = get_is_deleted();
    sing(Events::close_old, this);
    if (!local_is_deleted)
      remove();
  }

  bool Flower_Old::clips_children() {
    return style.get() && style->get_overflow() == Overflow::hidden;
  }

  void Flower_Old::update(float delta) {
    for (auto &child: children) {
      child->update(delta);
    }
  }

}