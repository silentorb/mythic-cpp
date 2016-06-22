#pragma once

namespace lookinglass {

  class Graphic_Options {
      int multisampling = 0;

  public:

      int get_multisampling() const {
        return multisampling;
      }

      void set_multisampling(int value) {
        multisampling = value;
      }
  };
}