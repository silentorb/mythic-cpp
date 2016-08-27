#pragma once

#include <resourceful/Resource.h>
#include "Texture.h"

namespace texturing {

  class MYTHIC_EXPORT Frame_Buffer : public resourceful::Resource {
      unsigned int id = 0;
      int width, height;
      texturing::Texture *texture;

  public:
      Frame_Buffer(int width, int height);
      void activate();
      static void deactivate();

      virtual void load() override;
      virtual void release() override;

      int get_width() const {
        return width;
      }

      int get_height() const {
        return height;
      }
  };
}