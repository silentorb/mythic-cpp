#pragma once

#include "Flower.h"
#include "Child.h"
#include <memory>
#include <vector>

using namespace std;

namespace bloom {
  namespace flowers {
    class BLOOM_EXPORT Parent : public virtual Flower {
    protected:
        vector<unique_ptr<Child>> children;

    public:
//        virtual void update_layout(Axis_Measurements &parent_measurements, Axis_Values &parent_bounds) override;
        virtual void update(float delta) override;
        virtual void render() override;

        void add_child(Child *child);

    };

  }
}