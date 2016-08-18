//#pragma once
//
//#include <aura/graphing/Node.h>
//
//namespace aura {
//  namespace graphing {
//    namespace nodes {
//
//      struct Frequency_Modulator_Data {
//          float first;
//          float second;
//          float frequency;
//          float strength;
//          float output;
//      };
//
//      class AURA_EXPORT Frequency_Modulator : public Node {
//          Input<float> first_property;
//          Input<float> second_property;
//          Input<float> frequency_property;
//          Input<float> strength_property;
//          Output<float> output;
//
//      public:
//          Frequency_Modulator() :
//            first_property(this),
//            second_property(this),
//            frequency_property(this),
//            strength_property(this),
//            output(this) {
//
//          }
//
//          virtual void update(const Stroke &stroke, void *raw_data) override {
//            auto &data = *(Frequency_Modulator_Data *) &raw_data;
//
//          }
//      };
//    }
//  }
//}