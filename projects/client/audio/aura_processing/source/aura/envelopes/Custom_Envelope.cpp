#include <stdexcept>
#include "Custom_Envelope.h"

using namespace std;

namespace aura {
  namespace envelopes {

    Custom_Envelope_Instance::Custom_Envelope_Instance(const Custom_Envelope &envelope, double duration) {
      envelope.initialize_instance(*this, duration);
    }
  }
}

