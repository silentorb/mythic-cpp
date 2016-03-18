#pragma once

#include "resourceful/Resource.h"
#include "Texture_Generator.h"
#include <memory>
#include <string>

using namespace std;

namespace texturing {

  struct Pixel {
      unsigned char r;
      unsigned char g;
      unsigned char b;
      unsigned char a;
  };

  class MYTHIC_EXPORT Texture : public resourceful::Resource {
      unsigned int id;
      int width, height;
      unique_ptr<Texture_Generator_Old> generator_old;
      Texture_Generator generator;

  public:
      Texture(int width, int height, Texture_Generator_Old *generator);
      Texture(int width, int height, Texture_Generator generator);
      Texture(Texture_Generator_Old *generator);
      Texture(const string filename);

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
