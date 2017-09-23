#pragma once

#include <vector>
#include "Trigger.h"
#include <memory>
#include "commoner/dllexport.h"

using namespace std;

namespace haft {

  class MYTHIC_EXPORT Device {
      string name;
      vector<unique_ptr<Trigger>> triggers;
      Device &operator=(const Device &) = delete;
      Device(Device const &) = delete;
      vector<Trigger *> active_triggers;

  public:

      Device(const string &name) : name(name) {}

      Device(const string &name, initializer_list<Trigger *> triggers);

      void add_trigger(Trigger *trigger) {
        triggers.push_back(unique_ptr<Trigger>(trigger));
      }

      Trigger &get_trigger(int index) const {
        return *triggers[index];
      }

      Trigger *get_trigger(const string trigger_name) const;

      const string &get_name() const {
        return name;
      }

      void assign(int index, Action &action) {
        auto &trigger = *triggers[index].get();
        trigger.set_action(action);
        active_triggers.push_back(&trigger);
      }

      void assign(const string trigger_name, Action &action) {
        auto trigger = get_trigger(trigger_name);
        if (trigger) {
          trigger->set_action(action);
          active_triggers.push_back(trigger);
        }
      }

      void assign(Trigger &trigger, Action &action) {
        trigger.set_action(action);
        active_triggers.push_back(&trigger);
      }

      const std::vector<Trigger *> get_active_triggers() const {
        return active_triggers;
      }
  };

}
