#pragma once

#include <resourceful/Resource.h>
#include <glm/vec2.hpp>

namespace texturing {
  namespace buffering {

    class Render_Buffer : public resourceful::Resource {
        unsigned int id = 0;
        glm::ivec2 dimensions;
        int multisamples = 0;

    public:
        Render_Buffer(const glm::ivec2 &dimensions, int multisamples);
        virtual ~Render_Buffer();
        void activate();

        virtual void load() override;
        virtual void release() override;

        unsigned int get_id() const {
          return id;
        }

    };
  }
}