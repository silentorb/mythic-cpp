#include "Texture_From_File.h"
#include "loader.h"

namespace texturing {

  unsigned char *Texture_From_File::generate(int &width, int &height) {
    return load_png(filename.c_str(), width, height);
  }
}