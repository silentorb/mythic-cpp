#pragma once

#include "Flower.h"
#include "Events.h"
#include "Parent.h"

namespace songbird {
  class Singer;
}

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Interactive : public Child {
        unique_ptr<songbird::Singer> singer;

    public:
        Interactive(Parent *parent);
        virtual ~Interactive();

        virtual glm::vec2 update_relative(const Parent_Dimensions &parent_dimensions) override;
        virtual void update_absolute(const glm::vec2 &parent_position) override;
        virtual void update(float delta) override;
        virtual void render() override;
        virtual const Axis_Values &get_absolute_bounds() override;
        void click(Flower_Delegate action);
    };
  }
}