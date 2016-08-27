#pragma once

#include <bloom/flowers/Single_Parent.h>

namespace texturing {
  class Frame_Buffer;

  class Texture;
}

namespace bloom {
  namespace flowers {

    class MYTHIC_EXPORT Buffered_Flower : public flowers::Single_Parent {
        texturing::Frame_Buffer *frame_buffer = nullptr;

        void prepare_frame_buffer();

    public:
        virtual void render() override;
        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;
    };
  }
}