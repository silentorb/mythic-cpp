#pragma once

#include <string>

namespace achieving {

  class Achievement_Definition {
      std::string key;
      std::string title;
      int range;

  public:
      Achievement_Definition() :
        key(""), title(""), range(1) {}

      Achievement_Definition(const std::string &key, const std::string &title, int range = 1) :
        key(key), title(title), range(range) {}

      const std::string &get_title() const {
        return title;
      }

      void set_title(const std::string &title) {
        Achievement_Definition::title = title;
      }

      const std::string &get_key() const {
        return key;
      }

      void set_key(const std::string &key) {
        Achievement_Definition::key = key;
      }

      int get_range() const {
        return range;
      }

      void set_range(int range) {
        Achievement_Definition::range = range;
      }
  };
}