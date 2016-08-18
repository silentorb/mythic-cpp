#include <aura/engineer/Engineer.h>
#include <aura/music/performance/Producer.h>
#include "Loop_Node.h"

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Oscillator_Data {
          Loop loop;
          float frequency;
          float output;
      };

      Node Loop_Node(const Node &frequency_source) {
        return Node(
          NODE_ID("Loop")
          {
            new Internal<Loop>([](void *data, Producer &producer, const Stroke & stroke) {
              new(data) Loop(producer.get_engineer().get_sample_rate());
            }),
            new Input<float>(frequency_source),
            new Output<float>(),
          },
          [](const Stroke &stroke, void *raw_data) {
            auto &data = *(Oscillator_Data *) raw_data;
            data.loop.set_frequency(data.frequency);
            data.output = data.loop.next();
          });
      }
    }
//      Loop_Node::Loop_Node(Node *frequency_source) :
//        loop(this, [](void *data, Producer & producer) {
//          new(data) Loop(producer.get_engineer().get_sample_rate());
//        }),
//        frequency(this),
//        output(this), Node(<#initializer#>) {
//        frequency.set_other_property(frequency_source);
//
//      }
//
//      Loop_Node::~Loop_Node() {
//
//      }

//      Internal<Loop> loop;
//      Input<float> frequency;
//      Output<float> output;
//
//      Loop_Node(Node *frequency_source);
//      virtual ~Loop_Node();
//
//      virtual void update(const Stroke &stroke, void *raw_data) override {
//        auto &data = *(Oscillator_Data *) raw_data;
//        data.loop.set_frequency(data.frequency);
//        data.output = data.loop.next();
//      }
//    }
  }
}