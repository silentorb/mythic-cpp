#pragma once

#include "signal_graph/Node.h"
#include "Loop_Node.h"
#include <cmath>
#include <math/utility.h>
#include <signal_graph/default_externals.h>

namespace aura {
  namespace graphing {
    namespace nodes {


      template<typename Externals>
      class Sine_Instance : public signal_graph::Node_Instance<Externals> {
          float position;
          float output;

      public:
          Sine_Instance(Externals &externals) :
            signal_graph::Node_Instance<Externals>(externals) {}

          virtual void update(Externals &externals) override {
            output = sin(position * 2 * Pi);
          }

          virtual const void *get_data() override {
            return &position;
          }
      };

      template<typename Externals>
      class Saw_Instance : public signal_graph::Node_Instance<Externals> {
          float position;
          float output;

      public:
          Saw_Instance(Externals &externals) :
            signal_graph::Node_Instance<Externals>(externals) {}

          virtual void update(Externals &externals) override {
            output = std::abs(fmod(position, 2) - 1);
          }

          virtual const void *get_data() override {
            return &position;
          }
      };

      template<typename Externals>
      signal_graph::Node Sine_Wave_With_Position_Source(const signal_graph::Node &position_source) {
        return Sine_Instance<Externals>::create_node(
          {
            new signal_graph::Input<float>(position_source),
            new signal_graph::Output<float>,
          }
        );
      }

      NODE_TEMPLATE
      signal_graph::Node Sine_Wave(const signal_graph::Node &frequency) {
        return Sine_Wave_With_Position_Source<Default_Externals>(Loop_Node<Default_Externals>(frequency));
      }

      template<typename Externals>
      signal_graph::Node Saw_Wave_With_Position_Source(const signal_graph::Node &position_source) {
        return Saw_Instance<Externals>::create_node(
          {
            new signal_graph::Input<float>(position_source),
            new signal_graph::Output<float>,
          }
        );
      }

      NODE_TEMPLATE
      signal_graph::Node Saw_Wave(const signal_graph::Node &frequency) {
        return Saw_Wave_With_Position_Source<Default_Externals>(Loop_Node<Default_Externals>(frequency));
      }
    }
  }
}