#include "Envelope.h"

namespace aura {

  Envelope::Envelope(initializer_list<Curve> initializer) :
    curves(initializer) { }
}