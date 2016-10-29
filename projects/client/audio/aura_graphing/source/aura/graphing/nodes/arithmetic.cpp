#include "arithmetic.h"

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Operator_Data {
          float first;
          float second;
          float output;
      };

      template<typename T>
      Node Operator(const Node &first, const Node &second, const Node_Update &update) {
        return Node(
          NODE_ID("Operator")
          {
            new Input<T>(first),
            new Input<T>(second),
            new Output<T>(),
          }, update);
      }

      Node Add(const Node &first, const Node &second) {
        return Operator<float>(first, second, [](const Stroke &stroke, void *raw_data) {
          auto &data = *(Operator_Data *) raw_data;
          data.output = data.first + data.second;
        });
      }

      Node Multiply(const Node &first, const Node &second) {
        return Operator<float>(first, second, [](const Stroke &stroke, void *raw_data) {
          auto &data = *(Operator_Data *) raw_data;
          data.output = data.first * data.second;
        });
      }
    }
  }
}