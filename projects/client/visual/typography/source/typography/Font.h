#pragma once

#include "commoner/dllexport.h"
#include "resourceful/Resource.h"
#include <string>
#include <map>
#include <memory>
#include <glm/vec2.hpp>

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

  struct Internal_Font;

  class MYTHIC_EXPORT Font : public resourceful::Resource, no_copy {
      string filename;
      unsigned int texture;
      glm::ivec2 dimensions;
      string name;

      std::map<char, std::unique_ptr<Character>> characters;
      void generate_texture();
      glm::ivec2 determine_texture_dimensions();
      unique_ptr<Internal_Font> internal;

  public:
      Font(const string name,const string filename, const void *library);
      ~Font();
      virtual void release() override;
      virtual void load() override;

      const string &get_name() const {
        return name;
      }

      const glm::ivec2 &get_dimensions() const {
        return dimensions;
      }

      const map<char, std:: unique_ptr<Character>> &get_characters() const {
        return characters;
      }

      void activate();
  };
}