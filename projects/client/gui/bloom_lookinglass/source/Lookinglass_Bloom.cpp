#include "Lookinglass_Bloom.h"
#include <bloom/Garden.h>
#include <glow.h>
#include "lookinglass/Lookinglass_Resources.h"
#include "lookinglass/House.h"
#include <drawing/Draw.h>

Lookinglass_Bloom::Lookinglass_Bloom(lookinglass::House &house, drawing::Draw &draw) :
  house(house), draw(draw) {

}

void Lookinglass_Bloom::render(bloom::Garden &garden) {
  enable_3d(false);
  garden.render();
  enable_3d(true);
}

void Lookinglass_Bloom::enable_3d(bool value) {
  draw.set_depth(value);
}

const framing::Frame_Info &Lookinglass_Bloom::get_frame() const {
  return draw.get_frame();
}

void Lookinglass_Bloom::draw_square(float left, float top, float width, float height, const glm::vec4 &color,
                                    bool solid) {

  draw.draw_square(left, top, width, height, color, solid);
}

typography::Font &Lookinglass_Bloom::get_font(const string &name) const {
  auto &resources = house.get_resources();
  return resources.get_font(name);
}

typography::Text_Effect &Lookinglass_Bloom::get_text_effect() const {
  auto &resources = house.get_resources();
  return resources.get_text_effect();
}

void Lookinglass_Bloom::enable_scissor_box(float left, float top, float width, float height) {
  glow::enable_scissor_box(left, top, width, height);
}

void Lookinglass_Bloom::disable_scissor_box() {
  glow::disable_scissor_box();
}
