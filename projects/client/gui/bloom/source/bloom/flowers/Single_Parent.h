#pragma once

#include "Common_Flower.h"
#include <memory>

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Single_Parent : public Common_Flower, public virtual Parent {
    protected:
        std::unique_ptr<Flower> child;

    public:
        virtual ~Single_Parent() {}
        virtual void add_child(Flower *child) override;
        virtual void insert(Flower *child, int index) override;
        virtual void remove_child(Flower *child) override;
        virtual void update(float delta) override;
        virtual void render() override;
        virtual bool check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) override;
        virtual bool affects_parent_dimensions() const override;
        virtual void clear() override;
        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) override;
        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;
        virtual int get_child_count() override;
        virtual Flower *get_child(int index) override;
    };
  }
}