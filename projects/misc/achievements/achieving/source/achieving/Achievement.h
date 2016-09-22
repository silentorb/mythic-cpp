#pragma once

#include "Achievement_Definition.h"
#include <functional>

namespace achieving {

  class Achievement;

  typedef std::function<void(const Achievement &, int)> Achievement_Progress_Setter;

  class Achievement {
      Achievement_Definition definition;
      Achievement_Progress_Setter progress_setter = nullptr;
      int progress = 0;

  public:
      Achievement() {}

      Achievement(const Achievement_Definition &definition, int progress = 0) :
        definition(definition), progress(progress) {}

      Achievement(const std::string &key, const std::string &title, int range = 1) :
        definition({key, title, range}) {}

      int get_progress() const {
        return progress;
      }

      bool is_completed() const {
        return progress == definition.get_range();
      }

      void set_progress_setter(const Achievement_Progress_Setter &setter) {
        progress_setter = setter;
      }

      void set_progress(int value, bool serialize = true) {
        if (progress != value) {
          progress = value;
          if (serialize)
            progress_setter(*this, value);
        }
      }

      const std::string &get_key() const {
        return definition.get_key();
      }

      const std::string &get_title() const {
        return definition.get_title();
      }
  };
}