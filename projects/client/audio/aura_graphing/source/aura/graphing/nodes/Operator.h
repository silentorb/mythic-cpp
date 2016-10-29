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
//      class Operator : public Node {
//      public:
//          Input<float> first;
//          Input<float> second;
//          Output<float> output;
//
//          Operator() :
//            first(this),
//            second(this),
//            output(this), Node(<#initializer#>) {
//
//          }
//
//          Operator(Node first_source, Node second_source): Operator(), Node(<#initializer#>) {
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