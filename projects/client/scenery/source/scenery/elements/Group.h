#pragma once

#include "dllexport.h"
#include "Spatial.h"
#include "Spatial_Source.h"
#include <vector>
#include <memory>

using namespace std;

namespace scenery {

  class MYTHIC_EXPORT Group : public virtual Parent, public Spatial {
      bool visible;

  protected:
      vector<unique_ptr<Element>> children;

  public:
      Group(Parent *parent = nullptr) : Spatial(parent) {}

      virtual ~Group() {}

      virtual void render() override;
      virtual void add_child(unique_ptr<Element> element) override;
      virtual void add_child(Element &element) override;
//      virtual bool has_transform() override;

      virtual void move_child(Element &element, Parent &destination) override;

      Element &get_child(int index) const {
        return *children[index];
      }

      virtual void remove_child(Element &element) override;
      void clear();

      virtual void update(float delta) override;

      vector<unique_ptr<Element>> &get_children() {
        return children;
      }

      bool is_visible() const {
        return visible;
      }

      void set_visible(bool value) {
        visible = value;
      }

      virtual void move_child(unique_ptr<Element> &element, Parent &destination) override;
      virtual Spatial_Source &get_spatial() override {
        return *this;
      }

  };
}