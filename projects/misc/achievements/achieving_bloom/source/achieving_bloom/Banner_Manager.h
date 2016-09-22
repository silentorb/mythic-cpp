#pragma once

#include <queue>
#include <functional>

namespace bloom {
  namespace flowers {
    class Parent;

    class Flower;
  }
}
namespace achieving {
  class Achievement;
}

namespace achieving_bloom {

  using Achievement_Banner_Delegate = std::function<void(const achieving::Achievement &, bloom::flowers::Flower *)>;
  using Banner_Creator = std::function<bloom::flowers::Flower *
    (const achieving::Achievement &achievement, const std::function<void()> &on_finished)>;

  class Banner_Manager {
      bloom::flowers::Parent &root;
      std::queue<const achieving::Achievement *> achievements;
      bloom::flowers::Flower *current_banner = nullptr;
      const Achievement_Banner_Delegate on_banner;
      const Banner_Creator banner_creator;

  public:
      Banner_Manager(bloom::flowers::Parent &root, const Banner_Creator &banner_creator,
                     const Achievement_Banner_Delegate on_banner = nullptr) :
        root(root), banner_creator(banner_creator), on_banner(on_banner) {}

      void add_achievement(const achieving::Achievement &achievement);
      void update();
  };
}