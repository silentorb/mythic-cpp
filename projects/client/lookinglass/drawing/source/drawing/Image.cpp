#include "Image.h"
#include "Sprite_Sheet_Info.h"

namespace drawing {

  Image::Image(const Sprite_Sheet_Info &sheet, texturing::Texture &texture, const string name, float left, float top,
               float right, float bottom, int pixel_width, int pixel_height) :
    sheet(sheet), texture(texture), name(name), left(left), top(top), bottom(bottom), right(right),
    pixel_width(pixel_width), pixel_height(pixel_height) { }

  float Image::get_width() const {
    return (float) pixel_width / sheet.get_pixel_width();
  }

  float Image::get_height() const {
    return (float) pixel_height / sheet.get_pixel_height();
  }
}