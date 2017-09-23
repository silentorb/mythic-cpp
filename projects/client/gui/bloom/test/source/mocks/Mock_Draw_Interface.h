#pragma once

#include <bloom/Draw_Interface.h>
#include <framing/Mutable_Frame.h>

using namespace bloom;
using namespace glm;
using namespace std;

class Mock_Draw_Interface : public Draw_Interface {

public:

//    virtual const glm::ivec2 get_dimensions() const override {
//      return ivec2(800, 600);
//    }

    Mock_Draw_Interface() {
      frame.set_dimensions(1000, 1000);
    }

    framing::Mutable_Frame frame;

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

    virtual const framing::Frame_Info &get_frame() const override {
      return frame;
    }

    virtual void enable_scissor_box(float left, float top, float width, float height) override {

    }

    virtual void disable_scissor_box() override {

    }


};