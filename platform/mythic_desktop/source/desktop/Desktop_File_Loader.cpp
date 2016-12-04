#include "Desktop_File_Loader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
namespace desktop {

  const string Desktop_File_Loader(const string &path) {
    ifstream file;
    auto full_path = "resources/" + path;

    file.open(full_path);
    if (!file.good())
      throw std::runtime_error(string("Could not open ") + full_path);

    stringstream stream;
    stream << file.rdbuf();
    return stream.str();
  }
}