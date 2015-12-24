#include <scenery/elements/Model.h>
#include <sculptor/create.h>
#include "Architecture_Lab.h"

using namespace scenery::elements;

namespace laboratory {

  Architecture_Lab::Architecture_Lab(Mythic_Engine &engine) :
    engine(engine) {
    scene = new Scene();
    engine.add_renderable(scene);
    camera = new Freeform_Camera();
    auto mesh = sculptor::create::box(vec3(1, 1, 1));
    auto mesh_data =
    auto model = new Model()
  }

  Architecture_Lab::~Architecture_Lab() {
    engine.remove_renderable(scene);
    delete scene;
    delete camera;
  }
}