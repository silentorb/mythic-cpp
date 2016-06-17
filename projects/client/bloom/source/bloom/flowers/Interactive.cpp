#include <songbird/Singer.h>
#include "Interactive.h"

namespace bloom {
  namespace flowers {

    Interactive::Interactive(Parent *parent) :
      Child(parent),
      singer(new songbird::Singer()) {
    }

    Interactive::~Interactive() { }

    void Interactive::click(Flower_Delegate action) {
      singer->listen(Events::activate, action);
    }

    glm::vec2 Interactive::update_relative(const Parent_Dimensions &parent_dimensions) {
      return {parent_dimensions.x.length, parent_dimensions.y.length};
    }

    void Interactive::update_absolute(const glm::vec2 &parent_position) {

    }

    void Interactive::update(float delta) {

    }

    void Interactive::render() {

    }

    const Axis_Values &Interactive::get_absolute_bounds() {
      throw runtime_error("Not supported.");
    }


  }
}