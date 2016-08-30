#pragma once

#include <bloom/flowers/Single_Parent.h>
#include "Buffered_Flower_Renderer.h"

namespace texturing {
  class Frame_Buffer;

  class Texture;
}

namespace bloom {
  namespace flowers {

    class MYTHIC_EXPORT Buffered_Flower : public flowers::Single_Parent {
        std::shared_ptr<texturing::Frame_Buffer> frame_buffer;
        std::shared_ptr<texturing::Texture> texture;
        int multisamples;

        std::shared_ptr<texturing::Frame_Buffer> multisample_frame_buffer;
        std::shared_ptr<texturing::Texture> multisample_texture;

        Buffered_Flower_Renderer renderer;

        void prepare_texture();

    public:
        Buffered_Flower(const Buffered_Flower_Renderer & renderer);
        virtual void render() override;
//        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;
    };
  }
}