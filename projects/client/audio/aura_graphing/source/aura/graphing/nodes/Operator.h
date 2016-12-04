//#pragma once
//#include <aura/graphing/Node.h>
//
//namespace aura {
//  namespace graphing {
//    namespace nodes {
////
////      struct Operator_Data {
////          float first;
////          float second;
////          float output;
////      };
//
//      class Operator : public signal_graph::Node {
//      public:
//          signal_graph::Input<float> first;
//          signal_graph::Input<float> second;
//          signal_graph::Output<float> output;
//
//          Operator() :
//            first(this),
//            second(this),
//            output(this), signal_graph::Node(<#initializer#>) {
//
//          }
//
//          Operator(signal_graph::Node first_source, signal_graph::Node second_source): Operator(), signal_graph::Node(<#initializer#>) {
//            first.set_other_property(first_source);
//            second.set_other_property(second_source);
//          }
//
//          virtual ~Operator() {
//
//          }
//      };
//    }
//  }
//}