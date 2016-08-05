#pragma once

#include <bloom/flowers/Box.h>

namespace scenery {
  class Scene;
}

namespace bloom {
namespace flowers {
  class MYTHIC_EXPORT Scene_Flower : public flowers::Box {
      shared_ptr<scenery::Scene> scene;

  public:
      Scene_Flower(shared_ptr<scenery::Scene> scene, flowers::Flower *parent);
      Scene_Flower(flowers::Flower *parent);

      virtual void render() override;

      const scenery::Scene &get_scene() const {
        return *scene;
      }

      void set_camera_angle(float degrees);
  };
}
}