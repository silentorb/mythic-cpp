#include <aura/engineer/Engineer.h>
#include "Loop_Node.h"

namespace aura {
  namespace graphing {
    namespace nodes {
      Loop_Node::Loop_Node(const Engineer &engineer, Output<float> &frequency_source) :
        loop(this, [& engineer](void *data) {
          new(data) Loop(engineer.get_sample_rate());
        }),
        frequency(this),
        output(this) {
        frequency.set_other_property(&frequency_source);

      }

      Loop_Node::~Loop_Node() {

      }
    }
  }
}