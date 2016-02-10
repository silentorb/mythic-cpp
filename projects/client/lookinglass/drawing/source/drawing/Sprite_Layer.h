#pragma once

#include "dllexport.h"
#include "Sprite.h"
#include <vector>
#include "lookinglass/Renderable.h"
#include <memory>
#include <vector>

namespace texturing {
  class Sprite_Sheet;
}

using namespace std;

namespace drawing {

  struct Vertex_Data {
      float x, y, u, v;
  };

  class MYTHIC_EXPORT Sprite_Layer : public lookinglass::Renderable {
      vector<Sprite *> sprites;
      Sprite_Sheet &sheet;
      unique_ptr<modeling::Simple_Mesh> mesh;
      Image_Effect *effect;
      vector<Vertex_Data> data;

  public:
      Sprite_Layer(Sprite_Sheet &sheet, Image_Effect &effect);
      ~Sprite_Layer();

      void add_sprite(Sprite &sprite);

      virtual void render(lookinglass::Glass &glass) override;
  };
}