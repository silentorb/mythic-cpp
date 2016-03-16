#include "Listener_Channel.h"
#include "Listener.h"

namespace songbird {

  Channel_Interface::~Channel_Interface() {
    if (listener)
      listener->remove_connection(this);
  }
}

