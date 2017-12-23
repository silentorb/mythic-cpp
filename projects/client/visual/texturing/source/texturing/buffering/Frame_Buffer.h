#pragma once

#include <resourceful/Resource.h>
#include "texturing/Texture.h"
#include <vector>
#include <memory>

namespace resourceful {
  class Resource_Handler;
}

namespace texturing {
  namespace buffering {

    class Render_Buffer;

    struct Attachment {
        std::shared_ptr<Render_Buffer> render_buffer;
        unsigned int port;
    };

    class Frame_Buffer : public resourceful::Resource {
        unsigned int id = 0;
//      std::shared_ptr<texturing::Texture> texture;
        std::vector<Attachment> attachments;

    public:
        Frame_Buffer();
        void set_draw();
        void set_read();
        static void deactivate();

        virtual void load() override;
        virtual void release() override;

        void attach_texture(texturing::Texture *texture);
        void attach_render_buffer(const shared_ptr<Render_Buffer> &render_buffer, unsigned int port);
        void check_complete();

        unsigned int get_id() const {
          return id;
        }

        virtual ~Frame_Buffer();
    };
  }
}