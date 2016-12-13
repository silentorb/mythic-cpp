#pragma once

namespace aura {

  template<typename Type>
  struct Primitive {
  protected:
      Type value;

  public:
      Primitive() {}

      Primitive(Type value) : value(value) {}

      Type get_value() const {
        return value;
      }
  };
}