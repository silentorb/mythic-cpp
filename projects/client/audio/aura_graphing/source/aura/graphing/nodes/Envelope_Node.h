#pragma once

#include "signal_graph/Node.h"
#include <aura/envelopes/Custom_Envelope.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Envelope_Node_Data {
          float output;
      };

      template<typename Externals>
      class Envelope_Node_Instance : public signal_graph::Node_Instance<Externals, Envelope_Node_Data> {
          envelopes::Custom_Envelope_Instance instance;
          const std::shared_ptr<envelopes::Custom_Envelope> &envelope;

      public:
          Envelope_Node_Instance(Externals &externals, const std::shared_ptr<envelopes::Custom_Envelope> &envelope) :
            signal_graph::Node_Instance<Externals, Envelope_Node_Data>(externals), envelope(envelope) {
            envelopes::Custom_Envelope::initialize_instance(instance, *envelope, externals.get_duration());
          }

          virtual void update(Externals &externals) override {
            data.output = envelope->update(instance, externals.get_progress(), externals.get_duration());
          }
      };

      template<typename Externals>
      class Envelope_Node_Definition : public signal_graph::Template_Node<Externals, Envelope_Node_Instance> {
          const std::shared_ptr<envelopes::Custom_Envelope> &envelope;

      public:
          Envelope_Node_Definition(const std::initializer_list<signal_graph::Property *> &property_initializer,
                                   const std::shared_ptr<envelopes::Custom_Envelope> &envelope) : Template_Node(
            property_initializer), envelope(envelope) {}

          virtual void initialize(void *data, const Externals &externals) const override {
            new (data) Envelope_Node_Instance<Externals>(externals, envelope);
          }
      };

      template<typename Externals>
      signal_graph::Node Envelope_Node(const std::shared_ptr<envelopes::Custom_Envelope> &envelope) {
        auto internal = std::shared_ptr<signal_graph::Node_Internal>(
          new Envelope_Node_Definition<Externals>(
            {
              new signal_graph::Output<float>(),
            }, envelope));
        return Node(internal);
      }

      signal_graph::Node
      Envelope_Node(std::initializer_list<envelopes::Point> points, const signal_graph::External_Base &duration,
                    const signal_graph::External_Base &progress) {
        return Envelope_Node(std::shared_ptr<envelopes::Custom_Envelope>(new envelopes::Custom_Envelope(points)),
                             duration, progress);
      }
//      signal_graph::Node Envelope_Node(const std::shared_ptr<envelopes::Custom_Envelope> &envelope, const signal_graph::External_Base &duration,
//                         const signal_graph::External_Base &progress);
//
//      signal_graph::Node Envelope_Node(std::initializer_list<envelopes::Point> points, const signal_graph::External_Base &duration,
//                                       const signal_graph::External_Base &progress);
    }
  }
}