#include "Texture.h"
#include "lookinglass/glow.h"

namespace shading {
  Texture::Texture(int width, int height, Texture_Generator *generator)
    : width(width), height(height),
      generator(generator) { }

  void Texture::load() {
    if (id)
      return;

    unique_ptr<float[]> data(new float[width * height * 3]);
    generator->generate(data.get(), width, height);

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, &data);

//  glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
  }

  void Texture::free() {
    if (!id)
      return;

    glDeleteTextures(1, &id);
    id = 0;
  }
}
