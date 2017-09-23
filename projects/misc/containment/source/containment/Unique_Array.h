#pragma once

#include <memory>
#include "Array.h"

namespace containment {

  template<typename T>
  class Unique_Array : public virtual Unique_Mutable_Container<T> {
      std::vector<std::unique_ptr<T>> items;
      std::unique_ptr<Container_Handler<T>> handler;

  public:
      Unique_Array(std::unique_ptr<Container_Handler<T>> &handler) :
        handler(std::move(handler)) {

      }

      typename std::vector<std::unique_ptr<T>>::iterator begin() const {
        return items.begin();
      }

      typename std::vector<std::unique_ptr<T>>::iterator end() const {
        return items.end();
      }

      std::unique_ptr<T> &operator[](size_t index) const {
        return items[index];
      }

      size_t size() const {
        return items.size();
      }

//      void push_back(T &item) {
//        items.push_back(item);
//        handler->on_add(item);
//      }

      void add(T *item) {
        items.push_back(std::unique_ptr<T>(item));
        handler->on_add(*item);
      }

      void add(std::unique_ptr<T> &item) override {
        items.push_back(std::move(item));
        handler->on_add(*item);
      }

      void remove(T &item) override {
        for (auto it = items.begin(); it != items.end(); it++) {
          if ((*it).get() == &item) {
            handler->on_remove(item);
            items.erase(it);
            break;
          }
        }
      }

      void clear() override {
        handler->on_clear();
        items.clear();
      }
  };
}