#pragma once

#include "dllexport.h"
#include "Element.h"
#include <vector>
#include <memory>

using namespace std;

namespace scenery {

  class MYTHIC_EXPORT Group : public Parent, public Element {
      vector<unique_ptr<Element>> elements;

  public:
      Group(Parent *parent) : Element(parent) { }

      virtual void render();
      virtual void add_child(unique_ptr<Element> element);
      virtual void add_child(Element &element);
      virtual bool has_transform() override;
      virtual mat4 get_transform() override;

      virtual void move_child(unique_ptr<Element> &element, Parent &destination) override;
      virtual void move_child(Element &element, Parent &destination) override;

      Element &get_child(int index) const {
        return *elements[index];
      }

      virtual void remove_child(Element &element) override;
      void clear();
  };
}