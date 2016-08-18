//#pragma once
//
//#include <aura/graphing/Node.h>
//
//namespace aura {
//  namespace graphing {
//    namespace nodes {
//
//      template<typename T>
//      AURA_EXPORT Node Constant(T value) {
//        return Node(
//          NODE_ID("Constant")
//          {
//            new Constant_Output<T>(value)
//          }, nullptr);
//      }
////      template<typename T>
////      class AURA_EXPORT Constant : public Node {
////          Constant_Output <T> output;
////
////      public:
////          Constant(T value) : output(value, this), Node(<#initializer#>) {}
////
////          virtual void update(const Stroke &stroke, void *raw_data) override {
////
////          }
////      };
//    }
//  }
//}