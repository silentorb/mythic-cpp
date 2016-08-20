#pragma once

#include <bloom/layout/Measurement.h>
#include "Box.h"

namespace bloom {
  namespace flowers {

    class Group;

    class BLOOM_EXPORT Box_Group : public Box {
        Group *group;

    public:
        Box_Group(Parent *parent = nullptr);

        virtual ~Box_Group() {}

        void clear();
        virtual void add_child(Flower *child) override;
        virtual void insert(Flower *child, int index) override;
        virtual void remove_child(Flower *child) override;
        virtual void update(float delta) override;
        virtual void render() override;
        virtual bool check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) override;

    };

//    glm::vec2 process_children(vector<unique_ptr<Flower>> &children, const glm::vec2 &parent_dimensions);

  }
}