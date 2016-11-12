#include <aura/engineering/Engineer.h>
#include "Loop_Node.h"

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Oscillator_Data {
          Loop loop;
          float frequency;
          float output;
      };

      signal_graph::Node Loop_Node(const signal_graph::Node &frequency_source, const signal_graph::External_Base &engineer) {
        return signal_graph::Node(
          NODE_ID("Loop")
          {
            new signal_graph::Internal<Loop>(),
            new signal_graph::Input<float>(frequency_source),
            new signal_graph::Output<float>(),
          },
          [& engineer](void *data, const signal_graph::Externals &externals) {
            new(data) Loop(externals.get_external<engineering::Engineer>(engineer).get_sample_rate());
          },
          [](void *raw_data, const signal_graph::Externals &externals) {
            auto &data = *(Oscillator_Data *) raw_data;
            data.loop.set_frequency(data.frequency);
            data.output = data.loop.next();
          });
      }
    }
//      Loop_Node::Loop_Node(signal_graph::Node *frequency_source) :
//        loop(this, [](void *data, Producer & producer) {
//          new(data) Loop(producer.get_engineer().get_sample_rate());
//        }),
//        frequency(this),
//        output(this), signal_graph::Node(<#initializer#>) {
//        frequency.set_other_property(frequency_source);
//
//      }
//
//      Loop_Node::~Loop_Node() {
//
//      }

//      signal_graph::Internal<Loop> loop;
//      signal_graph::Input<float> frequency;
//      signal_graph::Output<float> output;
//
//      Loop_Node(signal_graph::Node *frequency_source);
//      virtual ~Loop_Node();
//
//      virtual void update(const Stroke &stroke, void *raw_data, const signal_graph::Externals&externals) override {
//        auto &data = *(Oscillator_Data *) raw_data;
//        data.loop.set_frequency(data.frequency);
//        data.output = data.loop.next();
//      }
//    }
  }
}