#pragma once

#include <aura/graphing/Node.h>
#include <aura/envelopes/Custom_Envelope.h>

namespace aura {
  namespace graphing {
    namespace nodes {


      struct Envelope_Node_Data {
          envelopes::Custom_Envelope_Instance instance;
          float output;
      };

      Node Envelope_Node(const shared_ptr<envelopes::Custom_Envelope> &envelope) {
        return Node(
          NODE_ID("Envelope_Node")
          {
            new Internal<envelopes::Custom_Envelope_Instance>(
              [envelope](void *data, Producer &producer, const Stroke &stroke) {
                auto instance = new(data) envelopes::Custom_Envelope_Instance();
                envelopes::Custom_Envelope::initialize_instance(*instance, *envelope, stroke);
              }),
            new Output<float>(),
          },
          [envelope](const Stroke &stroke, void *raw_data) {
            auto &data = *(Envelope_Node_Data *) raw_data;
            data.output = envelope->update(data.instance, stroke);
          });
      }

      Node Envelope_Node(initializer_list<envelopes::Point> points) {
        return Envelope_Node(std::shared_ptr<envelopes::Custom_Envelope>(new envelopes::Custom_Envelope(points)));
      }
    }
  }
}