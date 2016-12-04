#pragma once

#include "signal_graph/Node.h"
#include <signal_graph/default_externals.h>

namespace signal_graph {

  template<typename T>
  struct Operator_Data {
      T first;
      T second;
      T output;
  };

  template<typename Externals, typename T>
  class Add_Node : public Node_Instance<Externals> {
      Operator_Data<T> data;

  public:
      Add_Node(Externals &externals) : Node_Instance<Externals>(externals) {}

      virtual void update(Externals &externals) override {
        data.output = data.first + data.second;
      }

      virtual const void *get_data() override {
        return &data;
      }
  };

  template<typename Externals, typename T>
  class Multiply_Node : public Node_Instance<Externals> {
      Operator_Data<T> data;

  public:
      Multiply_Node(Externals &externals) : Node_Instance<Externals>(externals) {}

      virtual void update(Externals &externals) override {
        data.output = data.first + data.second;
      }

      virtual const void *get_data() override {
        return &data;
      }
  };

  template<typename T, typename Node_Type>
  signal_graph::Node Operator(const signal_graph::Node &first, const signal_graph::Node &second) {
    return Node_Type::create_node(
      {
        new signal_graph::Input<T>(first),
        new signal_graph::Input<T>(second),
        new signal_graph::Output<T>(),
      });
  }
//
//  signal_graph::Node Add(const signal_graph::Node &first, const signal_graph::Node &second) {
//    return Operator<float>(first, second, [](void *raw_data, const signal_graph::Externals &externals) {
//      auto &data = *(Operator_Data *) raw_data;
//      data.output = data.first + data.second;
//    });
//  }
//
//  signal_graph::Node Multiply(const signal_graph::Node &first, const signal_graph::Node &second) {
//    return Operator<float>(first, second, [](void *raw_data, const signal_graph::Externals &externals) {
//      auto &data = *(Operator_Data *) raw_data;
//      data.output = data.first * data.second;
//    });
//  }

//  signal_graph::Node Add(const signal_graph::Node &first, const signal_graph::Node &second);
//  signal_graph::Node Multiply(const signal_graph::Node &first, const signal_graph::Node &second);

  NODE_TEMPLATE
  inline signal_graph::Node operator+(const signal_graph::Node &first, const signal_graph::Node &second) {
    return Operator<float, Add_Node<Default_Externals, float>>(first, second);
  }

  NODE_TEMPLATE
  inline signal_graph::Node operator*(const signal_graph::Node &first, const signal_graph::Node &second) {
    return Operator<float, Multiply_Node<Default_Externals, float>>(first, second);
  }

  NODE_TEMPLATE
  inline signal_graph::Node operator*(const signal_graph::Node &first, float value) {
    return Operator<float, Multiply_Node<Default_Externals, float>>(first, value);
  }

//      signal_graph::Node operator*(signal_graph::Node first, signal_graph::Node second) {
//        return nodes::Multiply(first, second);
//      }
}
//aura:: graphing::signal_graph::Node operator+(const aura:: graphing::signal_graph::Node &first, const aura:: graphing::signal_graph::Node &second) {
//  return aura:: graphing::nodes::Add(first, second);
//}
//
//aura:: graphing::signal_graph::Node operator*(const aura:: graphing::signal_graph::Node &first, const aura:: graphing::signal_graph::Node &second) {
//  return aura:: graphing::nodes::Multiply(first, second);
//}