#pragma once

#include "dllexport.h"
#include "resourceful/Resource.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "glm/glm.hpp"
#include <string>
#include <map>

using namespace std;

namespace typography {

  struct Character {
      glm::ivec2 size;       // Size of glyph
      glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
      unsigned int advance;
      // Offset to advance to next glyph
      float offset;
      float height;

      Character(const glm::ivec2 &size, const glm::ivec2 &bearing, unsigned int advance, float offset, float height)
        : size(size), bearing(bearing), advance(advance), offset(offset), height(height) { }
  };

  class MYTHIC_EXPORT Font : public resourceful::Resource {
      FT_Face face;
      string filename;
      const FT_Library &library;
      unsigned int texture;
      glm::ivec2 dimensions;
      string name;

      std::map<char, Character *> characters;
      void generate_texture();
      glm::ivec2 determine_texture_dimensions();

  public:
      Font(const string name,const string filename, const FT_Library &library);
      ~Font();
      virtual void free() override;
      virtual void load() override;

      const string &get_name() const {
        return name;
      }

      const glm::ivec2 &get_dimensions() const {
        return dimensions;
      }

      const map<char, Character *> &get_characters() const {
        return characters;
      }

      void activate();
  };
}