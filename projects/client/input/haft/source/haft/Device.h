#pragma once

#include <vector>
#include "Trigger.h"
#include <memory>


namespace haft {

  class Device {
      std::string name;
      std::vector<std::unique_ptr<Trigger>> triggers;
      Device &operator=(const Device &) = delete;
      Device(Device const &) = delete;
      std::vector<Trigger *> active_triggers;

  public:

      Device(const std::string &name) : name(name) {}

      Device(const std::string &name, std::initializer_list<Trigger *> triggers);

      void add_trigger(Trigger *trigger) {
        triggers.push_back(std::unique_ptr<Trigger>(trigger));
      }

      Trigger &get_trigger(int index) const {
        return *triggers[index];
      }

      Trigger *get_trigger(const std::string trigger_name) const;

      const std::string &get_name() const {
        return name;
      }

      void assign(int index, Action action) {
        auto &trigger = *triggers[index].get();
        trigger.set_action(action);
        active_triggers.push_back(&trigger);
      }

      template<typename T>
      void assign(const std::string trigger_name, T action) {
        auto trigger = get_trigger(trigger_name);
        if (trigger) {
          trigger->set_action(*(Action *) &action);
          active_triggers.push_back(trigger);
        }
      }

      void assign(const std::string trigger_name, Action action) {
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
