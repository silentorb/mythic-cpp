#pragma once

#include "commoner/dllexport.h"
#include <string>

namespace texturing {
  class Texture;
}

using namespace std;

namespace drawing {

  class Sprite_Sheet_Info;

  class MYTHIC_EXPORT Image {
      texturing::Texture &texture;
      const Sprite_Sheet_Info &sheet;
      const string name;
      float left, top, bottom, right;
      int pixel_width, pixel_height;

      Image(Image const &) = delete;
      Image &operator=(Image const &) = delete;
  public:

      Image(const Sprite_Sheet_Info &sheet, texturing::Texture &texture, const string name, float left, float top, float right, float bottom, int pixel_width,
            int pixel_height);

      texturing::Texture &get_texture() const {
        return texture;
      }

      float get_left() const {
        return left;
      }

      float get_top() const {
        return top;
      }

      float get_bottom() const {
        return bottom;
      }

      float get_right() const {
        return right;
      }

      int get_pixel_width() const {
        return pixel_width;
      }

      int get_pixel_height() const {
        return pixel_height;
      }


      const string &get_name() const {
        return name;
      }
  };

}