#pragma once

#include "resourceful/Resource.h"
#include "Texture_Generator.h"
#include <memory>
#include <string>
#include <glm/vec2.hpp>

using namespace std;

namespace texturing {

  struct Pixel {
      unsigned char r;
      unsigned char g;
      unsigned char b;
      unsigned char a;
  };

  class Texture : public resourceful::Resource {
      unsigned int id;
      glm::ivec2 dimensions;
//      unique_ptr<Texture_Generator_Old> generator_old;
      Texture_Generator generator;
      char multisamples = 0;

  public:
//      Texture(int width, int height, Texture_Generator_Old *generator);
      Texture(const glm::ivec2 &dimensions, Texture_Generator generator, char multisamples = 0);
//      Texture(Texture_Generator_Old *generator);
//      Texture(const string filename);

      virtual void release() override;
      virtual void load() override;

      void activate();

      int get_width() const {
        return dimensions.x;
      }

      int get_height() const {
        return dimensions.y;
      }

      const glm::ivec2 &get_dimensions() const {
        return dimensions;
      }

      void set_dimensions(const glm::ivec2 &value);

      unsigned int get_id() const {
        return id;
      }

      char get_multisamples() const {
        return multisamples;
      }

      unsigned int get_mode() const;
  };
}
