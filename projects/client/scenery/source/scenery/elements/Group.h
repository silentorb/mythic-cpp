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
      Group(Parent &parent) : Element(parent) { }
      virtual void render(lookinglass::Glass &glass);
      virtual void add(unique_ptr<Element> element);
      virtual bool has_transform() override;
      virtual mat4 get_transform() override;

      virtual void move_element(unique_ptr<Element> &element, Parent &destination) override;

      virtual void move_element(Element &element, Parent &destination) override;
  };
}