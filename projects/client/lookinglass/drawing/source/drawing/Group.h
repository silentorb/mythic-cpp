#pragma once

#include "dllexport.h"
#include "Element.h"
#include <vector>
#include <memory>

using namespace std;

namespace drawing {

  class MYTHIC_EXPORT Group : public Element {
  protected:
      vector<Element*> elements;

  public:
      ~Group();
      virtual void render() override;

      void add(Element &element) {
        elements.push_back(&element);
      }

      void move(Element& element, Group &target);

      void remove(Element &element);
  };
}
