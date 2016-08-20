#pragma once

#include "Flower.h"
#include "Events.h"
#include "Parent.h"

namespace songbird {
  class Singer;
}

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Interactive : public Flower {
        unique_ptr<songbird::Singer> singer;

    public:
        virtual bool check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) override;
        Interactive(Parent *parent);
        virtual ~Interactive();

        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) override;
        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;
        virtual void update(float delta) override;
        virtual void render() override;
        virtual const Axis_Values &get_absolute_bounds() const override;
        void click(Flower_Delegate action);
        bool static point_is_inside(const Flower *flower, const glm::vec2 &point);

        songbird::Singer &get_singer() const {
          return *singer;
        }
    };
  }
}