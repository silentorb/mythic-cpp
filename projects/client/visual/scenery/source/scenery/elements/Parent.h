#pragma once


#include <memory>
#include "Element.h"

using namespace std;

namespace scenery {


  class Parent : public virtual Element {
  public:
      virtual ~Parent();

      virtual void add_child(unique_ptr<Element> element) = 0;
            virtual void add_child(Element *element) = 0;
      virtual void remove_child(Element &element) = 0;
      virtual void move_child(Element &element, Parent &destination) = 0;
      virtual void move_child(unique_ptr<Element> &element, Parent &destination) = 0;
      virtual Spatial_Source &get_spatial() = 0;
  };
  inline Parent::~Parent() {}

}