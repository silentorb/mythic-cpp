#pragma once

#include "dllexport.h"
#include "Element.h"
#include <vector>
#include <memory>

using namespace std;

namespace scenery {

  class MYTHIC_EXPORT Group : public Element {
      vector<unique_ptr<Element>> elements;

  public:
      virtual void render(lookinglass::Glass &glass);
      void add(unique_ptr<Element> element);
  };
}