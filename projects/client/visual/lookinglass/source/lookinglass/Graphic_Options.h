#pragma once

namespace lookinglass {

  class Graphic_Options {
      int width;
      int height;
      int multisamples = 0;

  public:

      Graphic_Options() { }

      Graphic_Options(int width, int height) : width(width), height(height) { }

      int get_width() const {
        return width;
      }

      void set_width(int width) {
        Graphic_Options::width = width;
      }

      int get_height() const {
        return height;
      }

      void set_height(int height) {
        Graphic_Options::height = height;
      }

      int get_multisamples() const {
        return multisamples;
      }

      void set_multisamples(int value) {
        multisamples = value;
      }
  };
}