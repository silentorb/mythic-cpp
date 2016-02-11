#include <rapidjson/filereadstream.h>
#include "Sprite_Sheet_Info.h"
#include "rapidjson/document.h"
#include "texturing/Texture.h"

using namespace rapidjson;

namespace drawing {

  Sprite_Sheet_Info::Sprite_Sheet_Info(texturing::Texture &texture, const string path) {
    FILE *file = fopen(path.c_str(), "rb"); // non-Windows use "r"
    if (!file)
      throw std::runtime_error(string("Could not open ") + path);

    char readBuffer[65536];
    FileReadStream stream(file, readBuffer, sizeof(readBuffer));
    Document document;
    document.ParseStream(stream);
    fclose(file);

    pixel_width = document["width"].GetInt();
    pixel_height = document["height"].GetInt();
    const auto &sprites = document["sprites"];
    if (sprites.IsArray()) {
      for (SizeType i = 0; i < sprites.Size(); ++i) {
//        printf("a[%d] = %d\n", i, sprites[i].GetInt());
        const auto &sprite = sprites[i];

        int x = sprite["x"].GetInt();
        int y = (sprite["y"].GetInt() - 2);
        int width = sprite["width"].GetInt();
        int height = sprite["height"].GetInt();

        auto image = new Image(
          *this, texture,
          (float) x / pixel_width,
          (float) y / pixel_height,
          (float) (x + width) / pixel_width,
          (float) (y - height) / pixel_height,
          width,
          height
        );

//        auto image = new Image(
//          *this, texture,
//          (float) x,
//          (float) y,
//          (float) (x + width),
//          (float) (y + height),
//          width,
//          height
//        );

        images.push_back(unique_ptr<Image>(image));
      }
    }
  }
}