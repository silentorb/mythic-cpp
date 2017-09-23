#pragma once

#include "Element.h"
#include "Parent.h"
#include "Spatial_Source.h"

namespace scenery {

  class MYTHIC_EXPORT Simple_Element : public virtual Element {
  protected:
      Parent *parent = nullptr;

  public:
      Simple_Element() {
//        if (parent)
//          parent->add_child(unique_ptr<Element>(this));
      }
      ~Simple_Element() {}

      virtual Parent *get_parent() const override {
        return parent;
      }

      virtual void set_parent(Parent *new_parent, bool update_others = true) override;

      virtual void remove() {
        parent->remove_child(*this);
      }

      virtual void render() override {

      }

      virtual void update(float delta) override {

      }
  };
}