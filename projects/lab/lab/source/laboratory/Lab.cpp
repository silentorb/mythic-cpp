#include "Lab.h"
#include "laboratory/Architecture_Lab.h"
#include "laboratory/Sprite_Lab.h"

using namespace laboratory::display;

namespace laboratory {

  Lab::Lab(Mythic_Engine &engine) : Myth(engine) {
    initialize_display();
  }

  Lab::~Lab() {
//    delete camera;
  }

  void Lab::initialize_display() {
    if (false) {
      architecture_lab = unique_ptr<Architecture_Lab>(new Architecture_Lab(engine));
    }
    else {
      sprite_lab = unique_ptr<Sprite_Lab>(new Sprite_Lab(engine));
    }
  }

  void Lab::update(float delta) {
    if (false) {
      architecture_lab->update(delta);
    }
    else {
      sprite_lab->update(delta);
    }
  }


}