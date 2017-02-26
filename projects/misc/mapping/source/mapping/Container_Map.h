#pragma once

#include <memory>
#include <functional>
#include <map>
#include <containment/Container_Handler.h>
#include <containment/Mutable_Container.h>

namespace mapping {

  template<typename Input, typename Output>
  using Map_Factory = std::function<Output(Input &input)>;

  template<typename Input, typename Output>
  class Container_Map : public virtual containment::Container_Handler<Input> {
      containment::Mutable_Container<Output> &target_container;
      Map_Factory<Input, Output> factory;
      std::map<Input *, Output *> outputs;

  public:
      Container_Map(containment::Mutable_Container<Output> &target_container,
                    const Map_Factory<Input, Output> &factory)
        : target_container(target_container), factory(factory) {}

      void on_add(Input &item) override {
        auto new_item = factory(item);
        target_container.add(new_item);
      }

      void on_remove(Input &item) override {
        target_container.remove(*outputs[&item]);
      }

      void on_clear() override {
        target_container.clear();
      }
  };


  template<typename Input, typename Output>
  class Unique_Other_Container_Map : public virtual containment::Container_Handler<Input> {
      containment::Mutable_Container<Output> &target_container;
      Map_Factory<Input, std::unique_ptr<Output>> factory;
      std::map<Input *, Output *> outputs;

  public:
      Unique_Other_Container_Map(containment::Mutable_Container<Output> &target_container,
                    const Map_Factory<Input, std::unique_ptr<Output>> &factory)
        : target_container(target_container), factory(factory) {}

      void on_add(Input &item) override {
        auto new_item = factory(item);
        target_container.add(new_item);
      }

      void on_remove(Input &item) override {
        target_container.remove(*outputs[&item]);
      }

      void on_clear() override {
        target_container.clear();
      }
  };
}