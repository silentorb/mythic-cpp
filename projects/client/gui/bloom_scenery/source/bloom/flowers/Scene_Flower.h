#pragma once

#include <bloom/flowers/Common_Flower.h>
#include <bloom/flowers/Endpoint.h>

namespace scenery {
  class Scene;
}

namespace bloom {
  namespace flowers {

    class Scene_Flower : public flowers::Common_Flower, flowers::Endpoint {
        shared_ptr<scenery::Scene> scene;

    public:
        Scene_Flower(shared_ptr<scenery::Scene> scene, Parent *parent = nullptr);
        Scene_Flower(Parent *parent = nullptr);
        ~Scene_Flower();

        virtual void render() override;

        const scenery::Scene &get_scene() const {
          return *scene;
        }

        void set_camera_angle(float degrees);
    };
  }
}