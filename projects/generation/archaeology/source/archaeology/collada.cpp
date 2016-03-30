#include "collada.h"
#include "sculptor/geometry.h"
#include "pugixml.hpp"
#include <memory.h>
#include <iostream>
#include <textual/string_additions.h>

using namespace sculptor;
using namespace sculptor::geometry;
using namespace pugi;

namespace archaeology {

  struct Effect {
      vec4 color;
  };

  struct Material {
      vec4 color;
  };

  map<const string, Effect> load_effects(xml_node &collada) {
    map<const string, Effect> effects;
    auto library = collada.child("library_effects");
    for (auto effect_element: library.children("effect")) {
      auto profile = effect_element.child("profile_COMMON");
      auto technique = profile.child("technique");
			auto diffuse = technique.first_child().child("diffuse");
      auto color = diffuse.child("color");
      auto color_string = color.first_child().value();
      auto values = textual::split(color_string, ' ');
      Effect effect{
        vec4((float) atof(values[0].c_str()),
             (float) atof(values[1].c_str()),
             (float) atof(values[2].c_str()),
             (float) atof(values[3].c_str()))
      };

      auto id = effect_element.attribute("id").value();
      effects.emplace(std::make_pair(id, effect));
    }

    return effects;
  }

  map<const string, Material> load_materials(xml_node &collada) {
    auto effects = load_effects(collada);
    map<const string, Material> materials;
    auto library = collada.child("library_materials");
    for (auto material_element: library.children("material")) {
      auto instance_effect = material_element.child("instance_effect");
      auto effect_id = string(instance_effect.attribute("url").value()).substr(1); // Remove initial '#' from the string
      auto id = material_element.attribute("id").value();

      Material material{
        effects[effect_id].color
      };
      materials.emplace(std::make_pair(id, material));
    }

    return materials;
  }

  void load_geometry(xml_node &collada, Mesh *mesh, map<const string, Material> &materials) {
    auto library = collada.child("library_geometries");
    for (auto geometry: library.children("geometry")) {
      for (auto mesh_element : geometry.children("mesh")) {
        auto source = mesh_element.child("source");
        auto float_array = source.child("float_array");
        auto floats = float_array.first_child().value();
        auto values = textual::split(floats, ' ');
        Selection vertices;
        for (int i = 0; i < values.size(); i += 3) {
          vertices.push_back(mesh->add_vertex(vec3(
            (float) atof(values[i].c_str()),
            (float) atof(values[i + 1].c_str()),
            (float) atof(values[i + 2].c_str())
          )));
        }

        for (auto polygon_list : mesh_element.children("polylist")) {
          auto vcount = polygon_list.child("vcount");
          auto count_string = vcount.first_child().value();
          auto counts = textual::split(count_string, ' ');
          auto material_id = polygon_list.attribute("material").value();
          auto &material = materials[material_id];

          auto index_string = polygon_list.child("p").first_child().value();
          vector<string> indices;
          textual::split(index_string, ' ', indices);

          int step = 0;
          for (auto count_string : counts) {
            Selection polygon_vertices;
            int count = atoi(count_string.c_str());
            for (int i = 0; i < count; ++i) {
              int index = atoi(indices[step].c_str());
              step += 2;
              polygon_vertices.push_back(vertices[index]);
            }

            auto polygon = new Polygon(polygon_vertices);
            polygon->set_data("color", (float *) &material.color, 4);
//					polygon->flip();
            mesh->add_polygon(polygon);
          }
        }
      }
    }

  }

  unique_ptr<Mesh> load_collada_file(const string filename) {
    auto mesh = new Mesh();
    xml_document document;

    xml_parse_result info = document.load_file(filename.c_str());
    if (!info)
      throw runtime_error(string("Error loading Collada file: ") + info.description());

    auto collada = document.first_child();
    auto materials = load_materials(collada);
    load_geometry(collada, mesh, materials);
    return unique_ptr<Mesh>(mesh);
  }
}