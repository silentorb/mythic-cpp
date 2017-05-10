#pragma once

#include "iteration.h"
#include "Container_Handler.h"
#include "Unique_Mutable_Container.h"
#include <vector>
#include <memory>

namespace containment {

  template<typename T>
  class Iterator_Wrapper : public Iterator<T> {
      T *pointer;

  public:
      Iterator_Wrapper(T *pointer) : pointer(pointer) {}
  };

  template<typename T>
  class Array {
  protected:
      std::vector<T> items;
      std::unique_ptr<Container_Handler<T>> handler;

  public:
      Array(Container_Handler<T> *handler) : handler(handler) {}

      typename std::vector<T>::iterator begin() const {
        return items.begin();
      }

      typename std::vector<T>::iterator end() const {
        return items.end();
      }

      T operator[](size_t index) const {
        return items[index];
      }

      size_t size() const {
        return items.size();
      }

      void add(T &item) override {
        items.push_back(item);
        handler->on_add(item);
      }

      void remove(T &item) override {
        for (auto it = items.begin(); it != items.end(); it++) {
          if (it.get() == &item) {
            handler->on_remove(item);
            items.erase(it);
            break;
          }
        }
      }

//      void clear() override {
//        handler->on_clear();
//        items.clear();
//      }
  };

}