#pragma once

#include <songbird/Listener.h>
#include "Common_Flower.h"
#include "Endpoint.h"

namespace bloom {
  namespace flowers {
  
    class Listener_Flower : public Common_Flower, Endpoint {
        songbird::Listener listener;

    public:
        virtual ~Listener_Flower() { }

        songbird::Listener &get_listener() {
          return listener;
        }

        virtual const string get_class_name() const override {
          return "Listener_Flower";
        }
    };
  }
}