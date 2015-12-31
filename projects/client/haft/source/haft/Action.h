#pragma once

#include <string>

using namespace std;

namespace haft {
  class Action {
      string name;
      int id;

  public:
      Action(int id, const string &name) : name(name), id(id) { }
  };

}

