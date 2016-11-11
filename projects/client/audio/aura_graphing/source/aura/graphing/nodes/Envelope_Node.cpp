#include "Envelope_Node.h"

namespace aura {
  namespace graphing {
    namespace nodes {

      signal_graph::Node
      Envelope_Node(const std::shared_ptr<envelopes::Custom_Envelope> &envelope, const signal_graph::External &duration,
                    const signal_graph::External &progress) {
        return signal_graph::Node(
          NODE_ID("Envelope_Node")
          {
            new signal_graph::Internal<envelopes::Custom_Envelope_Instance>(),
            new signal_graph::Output<float>(),
          },
          [envelope, & duration](void *data, const signal_graph::Externals &externals) {
            auto instance = new(data) Envelope_Node_Data();
            double duration_value = externals.get_external<double>(duration);
            envelopes::Custom_Envelope::initialize_instance(instance->instance, *envelope, duration_value);
          },
          [envelope, &duration, &progress](void *raw_data, const signal_graph::Externals &externals) {
            auto &data = *(Envelope_Node_Data *) raw_data;
            double duration_value = externals.get_external<double>(duration);
            double progress_value = externals.get_external<double>(progress);
            data.output = envelope->update(data.instance, progress_value, duration_value);
          });
      }

      signal_graph::Node
      Envelope_Node(std::initializer_list<envelopes::Point> points, const signal_graph::External &duration,
                    const signal_graph::External &progress) {
        return Envelope_Node(std::shared_ptr<envelopes::Custom_Envelope>(new envelopes::Custom_Envelope(points)),
                             duration, progress);
      }
    }
  }
}