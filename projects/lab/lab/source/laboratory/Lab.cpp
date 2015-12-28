#include "Lab.h"
#include "laboratory/display/Lab_Renderer.h"
#include "laboratory/Architecture_Lab.h"

using namespace laboratory::display;

namespace laboratory {

  Lab::Lab(Mythic_Engine &engine) : Myth(engine) {
    initialize_display();
  }

  Lab::~Lab() {
//    delete camera;
  }

  void Lab::initialize_display() {
    architecture_lab = unique_ptr<Architecture_Lab>(new Architecture_Lab(engine));
//    renderer = new Lab_Renderer();
//    engine.add_renderable(renderer);

  }

  void Lab::update(float delta) {

  }


}