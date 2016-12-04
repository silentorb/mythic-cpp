#pragma once

#include <bloom/flowers/Box_Group.h>

namespace breeze {
  class Animation_Manager;
}
namespace achieving {
  class Achievement;
}
namespace achieving_bloom {

  namespace flowers {

    class Banner : public bloom::flowers::Box_Group {
        unique_ptr<breeze::Animation_Manager> animator;

        void initialize_appearance(const achieving::Achievement &achievement);

    public:
        Banner(const achieving::Achievement &achievement, const std::function<void()> &on_finished);
        virtual void update(float delta) override;
    };
  }
}