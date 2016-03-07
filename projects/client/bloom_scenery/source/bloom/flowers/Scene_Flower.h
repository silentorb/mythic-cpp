#pragma once

#include <bloom/flowers/Flower.h>

namespace scenery {
  class Scene;
}

namespace bloom {

  class MYTHIC_EXPORT Scene_Flower : public Flower {
      shared_ptr<scenery::Scene> scene;

  public:
      Scene_Flower(Garden &garden, shared_ptr<scenery::Scene> scene, Flower *parent);
      Scene_Flower(Garden &garden, Flower *parent);

      virtual void render() override;

      const scenery::Scene &get_scene() const {
        return *scene;
      }
  };
}