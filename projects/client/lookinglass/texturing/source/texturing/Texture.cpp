#include "Texture.h"
#include "lookinglass/glow.h"
#include <texturing/Texture_From_File.h>
#include "lookinglass/glow_gl.h"

namespace texturing {
//  Texture::Texture(int width, int height, Texture_Generator_Old *generator)
//    : id(0), width(width), height(height),
//      generator_old(generator) {
//    load();
//  }

  Texture::Texture(int width, int height, Texture_Generator generator, char mode)
    : id(0), width(width), height(height),
      generator(generator), multisamples(multisamples) {
    load();
  }

//  Texture::Texture(Texture_Generator_Old *generator)
//    : id(0), width(0), height(0),
//      generator_old(generator) {
//    load();
//  }

//  Texture::Texture(const string filename)
//    : id(0), width(0), height(0),
//      generator_old(new Texture_From_File(filename)) {
//    load();
//  }

  void Texture::load() {
    if (id)
      return;

    unsigned char *data = generator_old
                          ? generator_old->generate(width, height)
                          : generator(width, height);

    GLenum texture_mode = multisamples == 0
                          ? GL_TEXTURE_2D
                          : GL_TEXTURE_2D_MULTISAMPLE;
    
    glGenTextures(1, &id);
    glBindTexture(texture_mode, id);

//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
//    glTexParameteri(texture_mode, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(texture_mode, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(texture_mode, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

//    glTexParameteri(texture_mode, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (multisamples == 0) {
      glTexImage2D(texture_mode, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else {
      glTexImage2DMultisample(texture_mode, multisamples, GL_RGBA8, width, height, GL_TRUE);
    }

    glow::check_error("Creating texture.");

    glBindTexture(texture_mode, 0);

    delete data;
  }

  void Texture::release() {
    if (!id)
      return;

    glDeleteTextures(1, &id);
    id = 0;
  }

  void Texture::activate() {
    glBindTexture(GL_TEXTURE_2D, id);
  }
}
