#pragma once

#include <string>
#include "Action.h"

using namespace std;

namespace haft {
  class Trigger {
      string name;
      int id;
      Action *action;

  public:
      Trigger(const string &name, int id = 0)
        : name(name), id(id) { }

      Action *get_action() const {
        return action;
      }

      void set_action(Action &action) {
        this->action = &action;
      }

      const string &get_name() const {
        return name;
      }

      int get_id() const {
        return id;
      }
  };
}