#include <achieving/Achievement.h>
#include "Banner.h"
#include <breeze/Animation_Manager.h>
#include <bloom/flowers/Border.h>
#include <bloom/flowers/Fill.h>
#include <bloom/flowers/Text.h>

using namespace achieving;
using namespace breeze;
using namespace bloom;
using namespace glm;

namespace achieving_bloom {
  namespace flowers {

    static const float banner_height = 60;

    Banner::Banner(const Achievement &achievement, const std::function<void()> &on_finished) :
      animator(new Animation_Manager()) {
      initialize_appearance(achievement);
      static const float transition_duration = 0.3f;
      animator->animate2<Measurement_Accessor>(get_measurements().y.near, 0.0f, transition_duration,
                                               breeze::curves::bezier)
        .then([this]() -> Empty_Promise & {
          return animator->delay(4);
        })
        .then([this]() -> Empty_Promise & {
          return animator->animate2<Measurement_Accessor>(get_measurements().y.near, -banner_height,
                                                          transition_duration, breeze::curves::bezier);
        })
        .void_then([this, on_finished]() {
          remove();
          on_finished();
        });
    }

    void Banner::initialize_appearance(const Achievement &achievement) {
      insert(new bloom::flowers::Fill(vec4(vec3(0.1), 1)), 0);
      auto padding = new bloom::flowers::Box_Group(this);
      padding->set_top(20);
      padding->set_bottom(20);
      padding->set_dimensions({Measurements::shrink, 0}, {Measurements::shrink, 0});
      new bloom::flowers::Border(vec4(0.9, 0.9, 0.9, 1), 3, this);
      set_dimensions({Measurements::shrink, 0}, {Measurements::shrink, 0});
      set_dimensions(Measurements::stretch, banner_height);
      set_top(-banner_height);

      auto text_layout = new bloom::flowers::Box_Group(padding);
      auto text = new bloom::flowers::Text(achievement.get_title(), text_layout);
      text_layout->set_dimensions({Measurements::shrink, 0}, {Measurements::shrink, 0});
      text->set_size(16);
    }

    void Banner::update(float delta) {
      bloom::flowers::Single_Parent::update(delta);
      animator->update(delta);
    }
  }
}