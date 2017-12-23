#pragma once

#include <bloom/flowers/Single_Parent.h>
#include <texturing/buffering/Frame_Buffer.h>
#include "Buffered_Flower_Renderer.h"

namespace texturing {

  class Texture;

  namespace buffering {
    class Frame_Buffer;

    class Render_Buffer;
  }
}

namespace bloom {
  namespace flowers {

    class Buffered_Flower : public flowers::Single_Parent {
        std::shared_ptr<texturing::buffering::Frame_Buffer> frame_buffer;
        std::shared_ptr<texturing::Texture> texture;
        int multisamples;

//        std::shared_ptr<texturing::buffering::Frame_Buffer> multisample_frame_buffer;
//        std::shared_ptr<texturing::buffering::Render_Buffer> multisample_render_buffer;

        Buffered_Flower_Renderer renderer;

        void prepare_texture();

    public:
        Buffered_Flower(const Buffered_Flower_Renderer &renderer);
        virtual void render() override;
//        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;
    };
  }
}