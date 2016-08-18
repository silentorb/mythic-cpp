#pragma once

#include <aura/graphing/Node.h>
#include <cmath>
#include <math/utility.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Note_Frequency_Data {
          float output;
      };

      Node Note_Frequency() {
        return Node(
          NODE_ID("Note_Frequency")
          {
            new Output<float>(),
          },
          [](const Stroke &stroke, void *raw_data) {
            auto &data = *(Note_Frequency_Data *) raw_data;
            data.output = stroke.get_frequency();
          });
      }
//      class Note_Frequency : public Node {
//      public:
//          Output<float> output;
//
//          Note_Frequency() :
//            output(this), Node(<#initializer#>) {
//
//          }
//
//          virtual ~Note_Frequency() {
//
//          }
//
//          virtual void update(const Stroke &stroke, void *raw_data) override {
//            auto &data = *(Note_Frequency_Data *) raw_data;
//            data.output = stroke.get_frequency();
//          }
//      };
    }
  }
}