#pragma once

#include "resourceful/Resource.h"
#include "Texture_Generator.h"
#include <memory>

using namespace std;

namespace texturing {

  class MYTHIC_EXPORT Texture : public resourceful::Resource {
      unsigned int id;
      int width, height;
      unique_ptr<Texture_Generator> generator;

  public:
      Texture(int width, int height, Texture_Generator *generator);
      Texture(Texture_Generator *generator);

      virtual void free() override;
      virtual void load() override;

      void activate();

      int get_width() const {
        return width;
      }

      int get_height() const {
        return height;
      }

//      int get_id()const {
//        return id;
//      }
  };
}
