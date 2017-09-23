#pragma once
#include <memory>

namespace containment {

  template<typename T>
  class Mutable_Container {
  public:
      virtual void add(T &item) = 0;
      virtual void remove(T &item) = 0;
      virtual void clear() = 0;
  };
}