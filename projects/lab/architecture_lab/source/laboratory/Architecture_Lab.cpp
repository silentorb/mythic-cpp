#include <scenery/elements/Model.h>
#include <sculptor/create.h>
#include <lookinglass/modeling/mesh_export.h>
#include "Architecture_Lab.h"
#include "scenery/Scene.h"
#include <laboratory/display/Freeform_Camera.h>
#include <lookinglass/shading/Shader_Manager.h>

using namespace scenery::elements;

namespace laboratory {

  Architecture_Lab::Architecture_Lab(Mythic_Engine &engine) :
    engine(engine) {
    scene = new Scene();
    engine.add_renderable(scene);
    auto &client = engine.get_client();
    auto &house = client.get_house();
    auto &shader_manager = house.get_shader_manager();
    camera = new Freeform_Camera(house.get_base_viewport());
    auto mesh = sculptor::create::box(vec3(10, 10, 10));
    auto mesh_data = lookinglass::modeling::mesh_export::output_textured(*mesh);
    auto& program = shader_manager.create_program("solid",
                                                 *shader_manager.create_shader(Shader_Type::vertex,
                                                                               "scenery/solid.vertex"),
                                                 *shader_manager.create_shader(Shader_Type::fragment,
                                                                               "scenery/solid.fragment"));
    auto effect = shared_ptr<Spatial_Effect>(new Spatial_Effect(program));
    auto model = new Model(*mesh_data, effect);
    scene->add(model);
  }

  Architecture_Lab::~Architecture_Lab() {
    engine.remove_renderable(scene);
    delete scene;
    delete camera;
  }
}