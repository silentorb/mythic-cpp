#pragma once

#include <string>
#include "dllexport.h"

using namespace std;

namespace haft {
  class MYTHIC_EXPORT Action {
      string name;
      int id;

  public:
      Action(int id, const string &name) : name(name), id(id) { }

      const string &get_name() const {
        return name;
      }

      int get_id() const {
        return id;
      }

  };

}

