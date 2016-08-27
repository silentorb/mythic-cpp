//#include <rapidjson/filereadstream.h>
#include "Sprite_Sheet_Info.h"
//#include "rapidjson/document.h"
#include "texturing/Texture.h"

//using namespace rapidjson;

namespace drawing {

  Sprite_Sheet_Info::Sprite_Sheet_Info(texturing::Texture &texture, const string path) {
//    FILE *file = fopen(path.c_str(), "rb"); // non-Windows use "r"
//    if (!file)
//      throw std::runtime_error(string("Could not open ") + path);
//
//    char readBuffer[65536];
//    FileReadStream stream(file, readBuffer, sizeof(readBuffer));
//    Document document;
//    document.ParseStream(stream);
//    fclose(file);
//
//    pixel_width = document["width"].GetInt();
//    pixel_height = document["height"].GetInt();
//    const auto &sprites = document["sprites"];
//    if (sprites.IsArray()) {
//      for (SizeType i = 0; i < sprites.Size(); ++i) {
////        printf("a[%d] = %d\n", i, sprites[i].GetInt());
//        const auto &sprite = sprites[i];
//
//        int x = sprite["x"].GetInt();
//        int y = (sprite["y"].GetInt());
//        int width = sprite["width"].GetInt();
//        int height = sprite["height"].GetInt();
//
//        auto image = new Image(
//          *this, texture, sprite["name"].GetString(),
//          (float) x / pixel_width,
//          (float) (pixel_height - y) / pixel_height,
//          (float) (x + width) / pixel_width,
//          (float) (pixel_width - (y + height)) / pixel_height,
//          width,
//          height
//        );
//
//        images.push_back(unique_ptr<Image>(image));
//      }
//    }
  }

  Image &Sprite_Sheet_Info::get_image(const string &name) const {
    for (auto &image: images) {
      if (image->get_name() == name)
        return *image;
    }

    throw runtime_error("Could not find image " + name + ".");
  }

  int Sprite_Sheet_Info::get_image_index(const string &name) const {
    for (int i = 0; i < images.size(); ++i) {
      if (images[i]->get_name() == name)
        return i;
    }

    throw runtime_error("Could not find image " + name + ".");
  }
}