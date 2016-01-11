#pragma once

#include <vector>
#include "Trigger.h"
#include <memory>
#include "dllexport.h"

using namespace std;

namespace haft {

	class MYTHIC_EXPORT Device {
      string name;
      vector<unique_ptr<Trigger>> triggers;
			Device& operator=(const Device&) = delete;
			Device(Device const &) = delete;
	public:

      Device(const string &name) : name(name) { }

      Device(const string &name, initializer_list<Trigger *> triggers);

      void add_trigger(Trigger *trigger) {
        triggers.push_back(unique_ptr<Trigger>(trigger));
      }

      Trigger &get_trigger(int index) const {
        return *triggers[index];
      }

      Trigger &get_trigger(const string trigger_name) const;

      const string &get_name() const {
        return name;
      }

      void assign(int index, Action &action) {
        auto &trigger = *triggers[index].get();
        trigger.set_action(action);
      }

			void assign(const string trigger_name, Action &action) {
				auto &trigger = get_trigger(trigger_name);
				trigger.set_action(action);
			}

      void assign(Trigger &trigger, Action &action) {
        trigger.set_action(action);
        //        action.add_trigger(trigger);
      }
  };

}
