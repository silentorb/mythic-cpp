#pragma once

#include "Common_Flower.h"
#include "Parent.h"
#include <memory>
#include <vector>
#include <string>

using namespace std;

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Parent_Implementation : public Common_Flower, public virtual Parent {
    protected:
        vector<unique_ptr<Flower>> children;

    public:
        virtual ~Parent_Implementation();

        virtual bool check_event(const Event &event) override;

        Parent_Implementation(Parent *parent = nullptr) {
          Parent_Implementation::initialize_child(this, parent);
        }

        virtual void update(float delta) override;
        virtual void render() override;
        virtual void add_child(Flower *child) override;
        virtual void insert(Flower *child, int index) override;
        virtual void clear() override;

        static void initialize_child(Flower *child, Parent *parent);
        virtual void remove_child(Flower *child) override;
        virtual int get_child_count() override;
        virtual Flower *get_child(int index) override;

        virtual const string get_class_name() const override {
          return "Parent_Implementation";
        }
    };

  }
}