#pragma once

#include "commoner/dllexport.h"
#include <string>
#include "Action.h"

using namespace std;

namespace haft {

	class MYTHIC_EXPORT Trigger {
      string name;
      int id;
      Action *action;
			Trigger& operator=(const Trigger&) = delete;
			Trigger(Trigger const &) = delete;

	public:
      Trigger(const string &name, int id = 0)
        : name(name), id(id), action(nullptr) { }

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