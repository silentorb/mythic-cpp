#pragma once

#include <resourceful/Resource.h>
#include <glm/vec2.hpp>
#include "Texture.h"

namespace resourceful {
  class Resource_Handler;
}

namespace texturing {

  class MYTHIC_EXPORT Frame_Buffer : public resourceful::Resource {
      unsigned int id = 0;
//      glm::ivec2 dimensions;
//      std::shared_ptr<texturing::Texture> texture;
//      char multisamples = 0;
      void check_complete();

  public:
      Frame_Buffer();
      void activate();
      static void deactivate();

      virtual void load() override;
      virtual void release() override;

//      const glm::ivec2 &get_dimensions() const {
//        return dimensions;
//      }

//      void set_dimensions(const glm::ivec2 &value);
      void attach_texture(texturing::Texture *texture);

//      const shared_ptr<Texture> &get_texture() const {
//        return texture;
//      }

      virtual ~Frame_Buffer();
  };
}