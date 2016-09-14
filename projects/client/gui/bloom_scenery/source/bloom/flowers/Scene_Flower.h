#pragma once

#include <bloom/flowers/Common_Flower.h>

namespace scenery {
  class Scene;
}

namespace bloom {
namespace flowers {

  class MYTHIC_EXPORT Scene_Flower : public flowers::Common_Flower {
      shared_ptr<scenery::Scene> scene;

  public:
      Scene_Flower(shared_ptr<scenery::Scene> scene, Parent *parent);
      Scene_Flower(Parent *parent);
      ~Scene_Flower();

      virtual void render() override;

      const scenery::Scene &get_scene() const {
        return *scene;
      }

      void set_camera_angle(float degrees);
  };
}
}