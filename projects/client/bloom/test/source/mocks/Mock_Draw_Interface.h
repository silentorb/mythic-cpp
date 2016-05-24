#pragma once

#include <bloom/Draw_Interface.h>

using namespace bloom;
using namespace glm;
using namespace std;

class Mock_Draw_Interface: public Draw_Interface{

public:
    virtual const glm::ivec2 get_dimensions() const override {
      return ivec2(800, 600);
    }

    virtual void draw_square(float left, float top, float width, float height, const glm::vec4 &color,
                             bool solid) override {

    }

    virtual typography::Font &get_font(const std::string &name) const override {
      throw runtime_error("Not implemented.");
    }

    virtual typography::Text_Effect &get_text_effect() const override {
      throw runtime_error("Not implemented.");
    }

    virtual void enable_3d(bool value) override {

    }
};