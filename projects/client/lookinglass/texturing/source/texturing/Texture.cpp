#include "Texture.h"
#include "lookinglass/glow.h"

namespace texturing {
  Texture::Texture(int width, int height, Texture_Generator *generator)
    : id(0), width(width), height(height),
      generator(generator) {
    load();
  }

  Texture::Texture(Texture_Generator *generator)
    : id(0), width(0), height(0),
      generator(generator) {
    load();
  }

  void Texture::load() {
    if (id)
      return;

//    unique_ptr<float[]> data(new float[width * height * 3]);
    unsigned char *data = generator->generate(width, height);

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//    memset(data, 0, width * height * 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    lookinglass::glow::check_error("Creating texture.");

    glBindTexture(GL_TEXTURE_2D, 0);

    delete data;
  }

  void Texture::free() {
    if (!id)
      return;

    glDeleteTextures(1, &id);
    id = 0;
  }

  void Texture::activate() {
    glBindTexture(GL_TEXTURE_2D, id);
  }
}
