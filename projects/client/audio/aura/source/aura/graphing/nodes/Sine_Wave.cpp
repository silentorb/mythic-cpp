#include "Sine_Wave.h"
#include "Loop_Node.h"

namespace aura {
  namespace graphing {
    namespace nodes {
      Sine_Wave::Sine_Wave(const Engineer &engineer, Node *frequency_source) :
        Sine_Wave() {
        position.set_other_property(new Loop_Node(engineer, frequency_source));
      }
    }
  }
}

