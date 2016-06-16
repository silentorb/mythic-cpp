#pragma once

#include <bloom/flowers/Flower_Old.h>

namespace scenery {
  class Scene;
}

namespace bloom {

  class MYTHIC_EXPORT Scene_Flower : public Flower_Old {
      shared_ptr<scenery::Scene> scene;

  public:
      Scene_Flower(Garden &garden, shared_ptr<scenery::Scene> scene, Flower_Old *parent);
      Scene_Flower(Garden &garden, Flower_Old *parent);

      virtual void render() override;

      const scenery::Scene &get_scene() const {
        return *scene;
      }
  };
}