#pragma once

#include "dllexport.h"
//#include <functional>

//using namespace std;

namespace songbird {

  class Listener;

  struct MYTHIC_EXPORT Channel_Interface : no_copy {
      const void *id;
      Listener* listener = nullptr;

      virtual ~Channel_Interface();
      Channel_Interface(Channel_Interface&&) {}
      Channel_Interface() {}
  };

  template<typename T>
  struct MYTHIC_EXPORT Listener_Channel : public Channel_Interface {
      T dance;

      Listener_Channel(Listener_Channel<T> &&listener) : Channel_Interface(listener) { }
      Listener_Channel() { }

      virtual ~Listener_Channel() override { }
  };
}