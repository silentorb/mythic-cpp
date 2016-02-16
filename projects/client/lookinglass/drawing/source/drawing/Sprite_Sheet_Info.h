#pragma once

#include "dllexport.h"
#include "Image.h"
#include <memory>
#include <vector>

using namespace std;

namespace drawing {

  class MYTHIC_EXPORT Sprite_Sheet_Info {
      int pixel_width, pixel_height;
      vector<unique_ptr<Image>> images;

      Sprite_Sheet_Info(Sprite_Sheet_Info const &) = delete;
      Sprite_Sheet_Info &operator=(Sprite_Sheet_Info const &) = delete;

  public:
      Sprite_Sheet_Info(texturing::Texture &texture, const string path);

      Image &get_image(const string &name) const;
      int get_image_index(const string &name) const;

      Image &get_image(int index) const {
        return *images[index];
      }

      int get_pixel_width() const {
        return pixel_width;
      }

      int get_pixel_height() const {
        return pixel_height;
      }

  };
}