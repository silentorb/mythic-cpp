#pragma once

#include "dllexport.h"
//#include <functional>

//using namespace std;

namespace songbird {

  struct MYTHIC_EXPORT Listener_Interface {
      void *id;

      virtual ~Listener_Interface() { }
  };

  template<typename T>
  struct MYTHIC_EXPORT Listener : public Listener_Interface {
      T dance;

  };
}