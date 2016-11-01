#pragma once

#include "signal_graph/Node.h"

namespace signal_graph {

  signal_graph::Node Add(const signal_graph::Node &first, const signal_graph::Node &second);
  signal_graph::Node Multiply(const signal_graph::Node &first, const signal_graph::Node &second);

  inline signal_graph::Node operator+(const signal_graph::Node &first, const signal_graph::Node &second) {
    return Add(first, second);
  }

  inline signal_graph::Node operator*(const signal_graph::Node &first, const signal_graph::Node &second) {
    return Multiply(first, second);
  }

  inline signal_graph::Node operator*(const signal_graph::Node &first, float value) {
    return Multiply(first, value);
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