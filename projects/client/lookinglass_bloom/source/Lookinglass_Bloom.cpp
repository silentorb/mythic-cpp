#include "Lookinglass_Bloom.h"
#include <bloom/Garden.h>
#include "lookinglass/Lookinglass_Resources.h"
#include "lookinglass/House.h"

void Lookinglass_Bloom::register_renderable(bloom::Garden &garden) {
  draw.add_renderable([&]() {
    enable_3d(false);
    garden.render();
    enable_3d(true);
  });
}

void Lookinglass_Bloom::enable_3d(bool value) {
  draw.set_depth(value);
}

const glm::ivec2 Lookinglass_Bloom::get_dimensions() const {
  return draw.get_dimensions();
}

void Lookinglass_Bloom::draw_square(float left, float top, float width, float height, const glm::vec4 &color,
                                    bool solid) {

  draw.draw_square(left, top, width, height, color, solid);
}

typography::Font &Lookinglass_Bloom::get_font(const string &name) const {
  auto &resources = draw.get_house().get_resources();
  return resources.get_font(name);
}

typography::Text_Effect &Lookinglass_Bloom::get_text_effect() const {
  auto &resources = draw.get_house().get_resources();
  return resources.get_text_effect();
}



