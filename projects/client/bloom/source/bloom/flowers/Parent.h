#pragma once

#include "Flower.h"
#include <memory>
#include <vector>

using namespace std;

namespace bloom {
  namespace flowers {
    class BLOOM_EXPORT Parent : public Flower {
    public:
        virtual bool check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) override;

        Parent(Flower *parent) : Flower(parent) { }

        virtual void update(float delta) override;
        virtual void render() override;

    };

  }
}