#pragma once

#include <functional>
#include <string>

using namespace std;

namespace resourceful {
  typedef function<const string(const string &)> File_Loader;
}