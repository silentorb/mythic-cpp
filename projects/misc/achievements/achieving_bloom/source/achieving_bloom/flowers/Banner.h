#pragma once

#include <bloom/flowers/Box_Group.h>

namespace breeze {
  class Animator;
}
namespace achieving {
  class Achievement;
}
namespace achieving_bloom {

  namespace flowers {

    class Banner : public bloom::flowers::Box_Group {
        breeze::Animator& animator;

        void initialize_appearance(const achieving::Achievement &achievement);

        void initialize_animation(const std::function<void()> &on_finished);
    public:
        Banner(const achieving::Achievement &achievement, breeze::Animator& animator, const std::function<void()> &on_finished);
        virtual void update(float delta) override;
    };
  }
}