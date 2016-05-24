#pragma once

#include <bloom/Draw_Interface.h>
#include <drawing/Draw.h>
#include "dllexport.h"

namespace bloom {
  class Garden;
}

class MYTHIC_EXPORT Lookinglass_Bloom : public bloom::Draw_Interface, no_copy {
    drawing::Draw &draw;

public:
    virtual typography::Text_Effect &get_text_effect() const override;
    virtual const glm::ivec2 get_dimensions() const override;
    virtual void draw_square(float left, float top, float width, float height, const glm::vec4 &color,
                             bool solid) override;
    virtual typography::Font &get_font(const string &name) const override;

    Lookinglass_Bloom(drawing::Draw &draw) : draw(draw) { }

    void register_renderable(bloom::Garden &garden);
    virtual void enable_3d(bool value) override;

};