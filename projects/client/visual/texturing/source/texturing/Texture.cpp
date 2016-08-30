#include "Texture.h"
#include "glow.h"
#include <texturing/Texture_From_File.h>
#include "glow_gl.h"

namespace texturing {

  unsigned int Texture::get_mode() const{
    return get_multisamples() == 0
                          ? GL_TEXTURE_2D
                          : GL_TEXTURE_2D_MULTISAMPLE;
  }

  Texture::Texture(const glm::ivec2 &dimensions, Texture_Generator generator, char multisamples)
    : id(0), dimensions(dimensions),
      generator(generator), multisamples(multisamples) {
    load();
  }

  void Texture::load() {
    if (id)
      return;

    GLenum texture_mode = (GLenum)get_mode();

    glGenTextures(1, &id);
    glBindTexture(texture_mode, id);

//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
//    glTexParameteri(texture_mode, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(texture_mode, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(texture_mode, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

//    glTexParameteri(texture_mode, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (multisamples == 0) {
      if (generator) {
        unique_ptr<unsigned char> data(generator(dimensions.x, dimensions.y));
        glTexImage2D(texture_mode, 0, GL_RGBA, dimensions.x, dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.get());
      }
      else {
        glTexImage2D(texture_mode, 0, GL_RGBA, dimensions.x, dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
      }
    }
    else {
      glTexImage2DMultisample(texture_mode, multisamples, GL_RGBA, dimensions.x, dimensions.y, GL_TRUE);
    }

    glow::check_error("Creating texture.");

    glBindTexture(texture_mode, 0);
  }

  void Texture::release() {
    if (!id)
      return;

    glDeleteTextures(1, &id);
    id = 0;
  }

  void Texture::activate() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture((GLenum)get_mode(), id);
  }


  void Texture::set_dimensions(const glm::ivec2 &value) {
    if (dimensions == value)
      return;

    dimensions = value;
    release();
    load();
  }
}
