#include "Desktop_Shader_Loader.h"
#include <fstream>
#include <sstream>

namespace desktop {
  void Desktop_Shader_Loader::load(const char *path, string &result) {
    ifstream file;
    file.open(path);
    stringstream stream;
    stream << file.rdbuf();
    result = stream.str();
  }
}