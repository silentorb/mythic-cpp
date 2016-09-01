#pragma once

#include "aura/graphing/Node.h"

namespace aura {
  namespace graphing {
    namespace nodes {

      AURA_EXPORT Node Add(const Node &first, const Node &second);
      AURA_EXPORT Node Multiply(const Node &first, const Node &second);

      inline Node operator+(const Node &first, const Node &second) {
        return nodes::Add(first, second);
      }

      inline Node operator*(const Node &first, const Node &second) {
        return nodes::Multiply(first, second);
      }

      inline Node operator*(const Node &first, float value) {
        return nodes::Multiply(first, value);
      }

//      Node operator*(Node first, Node second) {
//        return nodes::Multiply(first, second);
//      }
    }
  }
}
//aura:: graphing::Node operator+(const aura:: graphing::Node &first, const aura:: graphing::Node &second) {
//  return aura:: graphing::nodes::Add(first, second);
//}
//
//aura:: graphing::Node operator*(const aura:: graphing::Node &first, const aura:: graphing::Node &second) {
//  return aura:: graphing::nodes::Multiply(first, second);
//}