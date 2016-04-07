#pragma once

#include "dllexport.h"
#include "Element.h"
#include <vector>
#include <memory>

using namespace std;

namespace scenery {

  class MYTHIC_EXPORT Group : public Parent, public Element {
  protected:
      vector<unique_ptr<Element>> children;

  public:
      Group(Parent *parent = nullptr) : Element(parent) { }

      virtual void render() override;
      virtual void add_child(unique_ptr<Element> element) override;
      virtual void add_child(Element &element) override;
      virtual bool has_transform() override;
      virtual mat4 get_transform() override;
      virtual mat4 get_absolute_orientation() override;

      virtual void move_child(unique_ptr<Element> &element, Parent &destination) override;
      virtual void move_child(Element &element, Parent &destination) override;

      Element &get_child(int index) const {
        return *children[index];
      }

      virtual void remove_child(Element &element) override;
      void clear();

      virtual void update(float delta) override;


  };
}