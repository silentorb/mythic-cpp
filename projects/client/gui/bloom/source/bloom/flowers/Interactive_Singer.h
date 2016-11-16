#pragma once

#include "Interactive.h"
#include <songbird/Singer.h>

namespace bloom {
  namespace flowers {

    class Interactive_Singer : public Interactive {
        unique_ptr<songbird::Singer> singer;

    public:
        Interactive_Singer() :
          singer(new songbird::Singer()) {}

        virtual ~Interactive_Singer() {

        }

        virtual bool check_event(const Event &event) override;

        void click(Flower_Delegate action);

        songbird::Singer &get_singer() const {
          return *singer;
        }

        virtual const string get_class_name() const override {
          return "Interactive_Singer";
        }
    };
  }
}