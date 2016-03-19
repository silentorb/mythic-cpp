#include "Font.h"
#include "lookinglass/glow.h"
#include <fstream>
#include <resourceful/path.h>

namespace typography {
  const unsigned char first_char = 33;
  const unsigned char last_char = 126;

  Font::Font(const string name, const string filename, const FT_Library &library) :
    name(name), filename(filename), library(library) {

    load();
  }

  Font::~Font() {
    free();
  }

  void Font::free() {
    for (auto &character: characters) {
      delete character.second;
    }

    characters.empty();
  }

  void Font::load() {
      
      auto root = string(MYTHIC_RESOURCES_PATH);
//      ifstream input( root + "/images/deevee.png");
//      auto good = input.good();
    auto path = root + filename;
      auto error = FT_New_Face(library, path.c_str(), 0, &face);
    if (error)
      throw runtime_error("ERROR::FREETYPE: Failed to load font: " + path);

    FT_Set_Pixel_Sizes(face, 0, 48);

    generate_texture();

    FT_Done_Face(face);
  }

  void Font::generate_texture() {
    dimensions = determine_texture_dimensions();
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    auto buffer = new unsigned char[dimensions.x * dimensions.y];
    memset(buffer, 0, dimensions.x * dimensions.y);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int memory_offset = 0;
    float vertical_offset = 0;
    for (unsigned char c = first_char; c <= last_char; c++) {
      if (FT_Load_Char(face, c, FT_LOAD_RENDER) != 0)
        throw runtime_error("Failed to load glyph");

      // A hack to work around an issue where the bitmap is not already rendered in certain cases.
      // This happens on the 32 bit Windows build  but not the 64 bit build.
      if (face->glyph->bitmap.buffer == NULL)
        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

      auto glyph = face->glyph;
      auto bitmap = face->glyph->bitmap;

      characters[(char) c] = new Character(
        glm::ivec2(bitmap.width, bitmap.rows),
        glm::ivec2(glyph->bitmap_left, glyph->bitmap_top),
        glyph->advance.x,
        vertical_offset / dimensions.y,
        (float) bitmap.rows / dimensions.y
      );

      for (int i = 0; i < bitmap.rows; i++) {
        memcpy(buffer + memory_offset, bitmap.buffer + i * bitmap.width, bitmap.width);
        memory_offset += dimensions.x;
      }

      vertical_offset += bitmap.rows;
    }

    glTexImage2D(
      GL_TEXTURE_2D, 0, GL_RED,
      dimensions.x,
      dimensions.y,
      0, GL_RED, GL_UNSIGNED_BYTE, buffer);

    glow::check_error("Loading texture.");
  }

  glm::ivec2 Font::determine_texture_dimensions() {
    unsigned int max_width = 0;
    unsigned int offset = 0;

    for (unsigned char c = first_char; c <= last_char; c++) {
      if (FT_Load_Char(face, c, FT_LOAD_RENDER) != 0)
        throw runtime_error("Failed to load glyph");

      if (face->glyph->bitmap.buffer == NULL)
        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

      auto glyph = face->glyph;
      auto bitmap = glyph->bitmap;
      if (bitmap.rows > max_width)
        max_width = bitmap.width;

      offset += bitmap.rows;
    }

    return glm::ivec2((int) max_width, (int) offset);
  }

  void Font::activate() {
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE0);
  }
}