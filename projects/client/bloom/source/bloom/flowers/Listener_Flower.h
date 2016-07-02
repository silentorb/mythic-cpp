#pragma once

#include <songbird/Listener.h>
#include "Flower.h"

namespace bloom {
  namespace flowers {
  
    class Listener_Flower : public Flower {
        songbird::Listener listener;

    public:
        virtual ~Listener_Flower() { }

        songbird::Listener &get_listener() {
          return listener;
        }
    };
  }
}