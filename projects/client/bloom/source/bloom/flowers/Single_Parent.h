#pragma once

#include "Common_Flower.h"
#include <memory>

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Single_Parent : public Common_Flower, public virtual Parent {
    protected:
        std::unique_ptr<Flower> child;

    public:
        virtual void add_child(Flower *child) override;
        virtual void insert(Flower *child, int index) override;
        virtual void remove_child(Flower *child) override;
        virtual void update(float delta) override;
        virtual void render() override;
        virtual bool check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) override;
    };
  }
}