#pragma once

#include "Common_Flower.h"
#include "Events.h"
#include "Parent_Implementation.h"
#include "Endpoint.h"

namespace songbird {
  class Singer;
}

namespace bloom {
  namespace flowers {

    class Interactive : public Common_Flower, Endpoint {

    public:
        Interactive(Parent *parent = nullptr);
        virtual ~Interactive();

        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) override;
        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;
        virtual void update(float delta) override;
        virtual void render() override;
        bool static point_is_inside(const Flower *flower, const glm::vec2 &point);

    };
  }
}