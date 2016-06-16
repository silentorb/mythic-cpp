#pragma once

#include "Flower.h"
#include <memory>
#include <vector>

using namespace std;

namespace bloom {
  namespace flowers {
    class BLOOM_EXPORT Parent : public virtual Flower {
        Flower *parent = nullptr;

    protected:
        vector<unique_ptr<Flower>> children;

    public:
        virtual void update_layout() override;
        virtual void update(float delta) override;
        virtual void render() override;
        virtual Flower *get_parent() const override;

    public:

    };
  }
}