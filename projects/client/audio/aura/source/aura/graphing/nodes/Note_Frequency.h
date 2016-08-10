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

      class Note_Frequency : public Node {
      public:
          Output<float> output;

          Note_Frequency() :
            output(this) {

          }

          virtual ~Note_Frequency() {

          }

          virtual void update(const Stroke &stroke, void *raw_data) override {
            auto &data = *(Note_Frequency_Data *) raw_data;
            data.output = stroke.get_frequency();
          }
      };
    }
  }
}