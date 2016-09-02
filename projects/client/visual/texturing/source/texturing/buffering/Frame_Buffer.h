#pragma once

#include <resourceful/Resource.h>
#include "texturing/Texture.h"

namespace resourceful {
  class Resource_Handler;
}

namespace texturing {
  namespace buffering {

    class Render_Buffer;

    class MYTHIC_EXPORT Frame_Buffer : public resourceful::Resource {
        unsigned int id = 0;
//      std::shared_ptr<texturing::Texture> texture;
        void check_complete();

    public:
        Frame_Buffer();
        void activate();
        static void deactivate();

        virtual void load() override;
        virtual void release() override;

        void attach_texture(texturing::Texture *texture);
        void attach_render_buffer(Render_Buffer *render_buffer);

        unsigned int get_id() const {
          return id;
        }

        virtual ~Frame_Buffer();
    };
  }
}