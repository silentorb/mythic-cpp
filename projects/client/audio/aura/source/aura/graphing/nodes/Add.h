//#pragma once
//#include "Operator.h"
//
//namespace aura {
//  namespace graphing {
//    namespace nodes {
//
//      class Add : public Operator {
//      public:
//          Add(Node first_source, Node second_source): Operator(first_source, second_source) {
//          }
//
//          virtual void update(const Stroke &stroke, void *raw_data) override {
//            auto &data = *(Operator_Data *) raw_data;
//            data.output = data.first + data.second;
//          }
//      };
//    }
//  }
//}