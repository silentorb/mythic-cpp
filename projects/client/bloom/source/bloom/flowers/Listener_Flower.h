#pragma once

#include <songbird/Listener.h>
#include "Common_Flower.h"

namespace bloom {
  namespace flowers {
  
    class Listener_Flower : public Common_Flower {
        songbird::Listener listener;

    public:
        virtual ~Listener_Flower() { }

        songbird::Listener &get_listener() {
          return listener;
        }
    };
  }
}