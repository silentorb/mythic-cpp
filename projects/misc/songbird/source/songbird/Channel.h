#pragma once

#include <commoner/no_copy.h>
#include "songbird_export.h"

//#include <functional>

//using namespace std;

namespace songbird {

  class Listener;

  struct SONGBIRD_EXPORT Channel_Interface : no_copy {
      const void *id;
      Listener *listener = nullptr;

      virtual ~Channel_Interface();

      Channel_Interface(Channel_Interface &&) {}

      Channel_Interface() {}
  };

  template<typename T>
  struct SONGBIRD_EXPORT Channel : public Channel_Interface {
      T dance;

      Channel(Channel<T> &&listener) : Channel_Interface(listener) {}

      Channel() {}

      virtual ~Channel() override {}
  };
}