#pragma once

#include <bloom/Draw_Interface.h>
#include "commoner/dllexport.h"
#include <string>

namespace bloom {
  class Garden;
}

namespace lookinglass {
  class House;
}

namespace drawing {
  class Draw;
}

class Lookinglass_Bloom : public bloom::Draw_Interface, no_copy {
    lookinglass::House &house;
    drawing::Draw &draw;

public:
    Lookinglass_Bloom(lookinglass::House &house, drawing::Draw &draw);
    virtual void enable_scissor_box(float left, float top, float width, float height) override;
    virtual void disable_scissor_box() override;
    virtual const framing::Frame_Info &get_frame() const override;
    virtual typography::Text_Effect &get_text_effect() const override;
    virtual void draw_square(float left, float top, float width, float height, const glm::vec4 &color,
                             bool solid) override;
    virtual typography::Font &get_font(const std::string &name) const override;


    void render(bloom::Garden &garden);
    virtual void enable_3d(bool value) override;

};