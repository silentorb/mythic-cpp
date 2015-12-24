#include "Lab.h"
#include "laboratory/display/Lab_Renderer.h"

using namespace laboratory::display;

namespace laboratory {

  Lab::Lab(Mythic_Engine &engine) : Myth(engine) {
    initialize_display();
  }

  Lab::~Lab() {
    delete camera;
  }

  void Lab::initialize_display() {

    camera = new Freeform_Camera();
    renderer = new Lab_Renderer();
    engine.add_renderable(renderer);
  }

  void Lab::update(float delta) {

  }
}