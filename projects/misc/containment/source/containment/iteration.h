#pragma once

#include <cstddef>

namespace containment {

  template<typename T>
  class Iterator {
      virtual bool operator!=(const Iterator<T> &other) const = 0;
      virtual T operator*() const = 0;
      virtual const Iterator<T> &operator++() = 0;
  };

  template<typename T>
  class Iterable {
  public:
      virtual Iterator<T> begin() const = 0;
      virtual Iterator<T> end() const = 0;
  };

  template<typename T>
  class Indexable : public virtual Iterable<T> {
  public:
      virtual T operator[](size_t index) const = 0;
      virtual size_t size() const = 0;
  };
}