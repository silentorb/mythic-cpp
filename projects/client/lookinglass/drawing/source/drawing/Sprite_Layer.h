#pragma once

#include "dllexport.h"
#include "Sprite.h"
#include <vector>
#include "lookinglass/Renderable.h"
#include <memory>
#include <vector>

namespace texturing {
  class Texture;
}

namespace modeling {
  class Simple_Mesh;
}

using namespace std;

namespace drawing {

  struct Vertex_Data {
      float x, y, u, v;
  };

  class MYTHIC_EXPORT Sprite_Layer : public lookinglass::Renderable {
      vector<Sprite *> sprites;
      Texture &texture;
      unique_ptr<modeling::Simple_Mesh> mesh;
      Image_Effect *effect;
      vector<Vertex_Data> data;

  public:
      Sprite_Layer(Texture &texture, Image_Effect &effect, Draw &draw);
      ~Sprite_Layer();

      void add_sprite(Sprite &sprite);

      virtual void render(lookinglass::Glass &glass) override;
  };
}