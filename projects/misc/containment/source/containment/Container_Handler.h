#pragma once

namespace containment {

  template<typename T>
  class Container_Handler {
  public:
      virtual void on_add(T &item) = 0;
      virtual void on_remove(T &item) = 0;
      virtual void on_clear() = 0;
  };

  template <typename T>
  class Empty_Container_Handler  : public virtual Container_Handler<T> {
  public:
      void on_add(T &item) override {

      }

      void on_remove(T &item) override {

      }

      void on_clear() override {

      }
  };
}