#pragma once

#include "dllexport.h"
//#include <functional>

//using namespace std;

namespace songbird {

  struct MYTHIC_EXPORT Listener_Interface : no_copy {
      const void *id;

      virtual ~Listener_Interface() { }
      Listener_Interface(Listener_Interface&&) {}
      Listener_Interface() {}
  };

  template<typename T>
  struct MYTHIC_EXPORT Listener : public Listener_Interface {
      T dance;

      Listener(Listener<T> &&listener) : Listener_Interface(listener) { }
      Listener() { }

      virtual ~Listener() override { }
  };
}