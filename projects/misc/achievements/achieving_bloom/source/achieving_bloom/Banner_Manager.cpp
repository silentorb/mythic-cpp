#include "Banner_Manager.h"
#include <bloom/flowers/Parent.h>
#include <achieving/Achievement.h>

using namespace bloom;

namespace achieving_bloom {

  void Banner_Manager::add_achievement(achieving::Achievement &achievement) {
    achievements.push(&achievement);
  }

  void Banner_Manager::update() {
    if (!current_banner && achievements.size()) {
      auto achievement = achievements.front();
      achievements.pop();
      current_banner = banner_creator(*achievement);
      root.add_child(current_banner);
    }
  }
}