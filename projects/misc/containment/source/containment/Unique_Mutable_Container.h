#pragma once
#include <memory>

namespace containment {

  template<typename T>
  class Unique_Mutable_Container {
  public:
      virtual void add(std::unique_ptr <T> &item) = 0;
      virtual void remove(T &item) = 0;
      virtual void clear() = 0;
  };
}