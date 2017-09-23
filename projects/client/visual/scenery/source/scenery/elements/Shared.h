#pragma once

#include "Parent.h"
#include "Spatial.h"

namespace scenery {

  template<typename T>
  class Shared : public Parent, Simple_Element {
      std::shared_ptr<T> child;

  public:
      void add_child(unique_ptr<Element> element) override {
        throw runtime_error("Not Implemented.");
      }

      void add_child(Element *element) override {
        throw runtime_error("Not Implemented.");
      }

      void add_child(std::shared_ptr<T> &element) {
        child = element;
        element->set_parent(this, false);
      }

      void remove_child(Element &element) override {

      }

      void move_child(Element &element, Parent &destination) override {
        throw runtime_error("Not Implemented.");
      }

      void move_child(unique_ptr<Element> &element, Parent &destination) override {
        throw runtime_error("Not Implemented.");
      }

      Spatial_Source &get_spatial() override {
        return parent->get_spatial();
      }
  };
}