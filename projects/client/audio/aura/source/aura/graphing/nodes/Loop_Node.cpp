#include <aura/engineer/Engineer.h>
#include <aura/music/performance/Producer.h>
#include "Loop_Node.h"
namespace aura {
  namespace graphing {
    namespace nodes {
      Loop_Node::Loop_Node(Node *frequency_source) :
        loop(this, [](void *data, Producer & producer) {
          new(data) Loop(producer.get_engineer().get_sample_rate());
        }),
        frequency(this),
        output(this) {
        frequency.set_other_property(frequency_source);

      }

      Loop_Node::~Loop_Node() {

      }
    }
  }
}