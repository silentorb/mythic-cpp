#include <scenery/elements/Model.h>
#include <sculptor/create.h>
#include <lookinglass/modeling/mesh_export.h>
#include "Architecture_Lab.h"
#include "scenery/Scene.h"
#include <laboratory/display/Freeform_Camera.h>

using namespace scenery::elements;

namespace laboratory {

  Architecture_Lab::Architecture_Lab(Mythic_Engine &engine) :
    engine(engine) {
    scene = new Scene();
    engine.add_renderable(scene);
    camera = new Freeform_Camera(engine.get_client()->get_house().get_base_viewport());
    auto mesh = sculptor::create::box(vec3(1, 1, 1));
    auto mesh_data = lookinglass::modeling::mesh_export::output_textured(*mesh);
    auto effect = shared_ptr<Spatial_Effect>(new Spatial_Effect());
    auto model = new Model(*mesh_data, effect);
    scene->add(model);
  }

  Architecture_Lab::~Architecture_Lab() {
    engine.remove_renderable(scene);
    delete scene;
    delete camera;
  }
}