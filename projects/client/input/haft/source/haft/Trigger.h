#pragma once


#include <string>
#include "Action.h"



namespace haft {

	class Trigger {
      std::string name;
      int id;
      Action action;
			Trigger& operator=(const Trigger&) = delete;
			Trigger(Trigger const &) = delete;

	public:
      Trigger(const std::string &name, int id = 0)
        : name(name), id(id), action(0) { }

      Action get_action() const {
        return action;
      }

      void set_action(Action &action) {
        this->action = action;
      }

      const std::string &get_name() const {
        return name;
      }

      int get_id() const {
        return id;
      }
  };
}