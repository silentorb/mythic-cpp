#include "collada.h"
#include "sculptor/geometry.h"
#include "pugixml.hpp"
#include <memory.h>
#include <iostream>
#include <textual/string_additions.h>
#include <sstream>

using namespace sculptor;
using namespace sculptor::geometry;
using namespace pugi;

#if ANDROID
#include <vector>
extern void android_load_binary(std::vector<char> &buffer, const std::string &path);
#endif

namespace archaeology {

  typedef function<void(sculptor::geometry::Polygon * , xml_node & )> Polygon_Delegate;

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
      auto phong = technique.first_child();
      auto diffuse = phong.child("diffuse");
      auto color = diffuse.child("color");
      auto color_string = color.first_child().value();
      auto values = textual::split(color_string, ' ');
      auto color_value = vec4((float) atof(values[0].c_str()),
                              (float) atof(values[1].c_str()),
                              (float) atof(values[2].c_str()),
                              (float) atof(values[3].c_str()));

      auto transparency = phong.child("transparency");
      if (transparency) {
        color_value.w = atof(transparency.child("float").first_child().value());
      }
      Effect effect{color_value};

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

  template<typename R, typename F>
  R next_value(const string &input, int &index, F f) {
    char buffer[20];
    int buffer_index = 0;
//    string result;
    for (int i = 0; i < 20; ++i) {
      if (index >= input.size()) {
        buffer[buffer_index] = 0;
        return (R) f(buffer);
      }

      auto character = input[index++];
      if (character == ' ') {
        buffer[buffer_index] = 0;
        return (R) f(buffer);
      }

      buffer[buffer_index++] = character;
//      result += character;
    }

    throw runtime_error("Invalid mesh data string.");
  }

  void foo(Polygon_Delegate action, Selection &vertices, xml_node &polygon_list) {
    auto vcount = polygon_list.child("vcount");
    string count_string = vcount.first_child().value();
    auto index_string = polygon_list.child("p").first_child().value();

    stringstream stream(index_string);
    string item;

    int step = 0;
    int count_index = 0, index_index = 0;
    while (count_string.size() > count_index) {
      Selection polygon_vertices;
      int count = next_value<int>(count_string, count_index, atoi);
      for (int i = 0; i < count; ++i) {
        getline(stream, item, ' ');
        int index = atoi(item.c_str());
        getline(stream, item, ' ');
        step += 2;
        polygon_vertices.push_back(vertices[index]);
      }

      auto polygon = new Polygon(polygon_vertices);
      action(polygon, polygon_list);
    }

  }

  void load_geometry2(xml_node &geometry, Basic_Mesh *mesh, Polygon_Delegate action) {
    for (auto mesh_element : geometry.children("mesh")) {
      auto source = mesh_element.child("source");
      auto float_array = source.child("float_array");
      string floats = float_array.first_child().value();
      Selection vertices;
      int float_index = 0;
      while (floats.size() > float_index) {
        vec3 temp;
        temp.x = next_value<float>(floats, float_index, atof);
        temp.y = next_value<float>(floats, float_index, atof);
        temp.z = next_value<float>(floats, float_index, atof);

        auto vertex = mesh->add_vertex(temp);
        vertex->reserve_polygons(4);
        vertices.push_back(vertex);
      }

      for (auto polygon_list : mesh_element.children("polylist")) {
        foo(action, vertices, polygon_list);
      }
    }
  }

  struct Vertex_Group_Data {
      string mesh_name;
      string data;
  };

  vector <Vertex_Group_Data> load_vertex_groups(xml_node &controllers) {
    vector<Vertex_Group_Data> result;
    for (auto controller : controllers.children("controller")) {
      auto skin = controller.child("skin");
      auto indices = skin.child("vertex_weights").child("v");
      string full_name = skin.attribute("source").value();
      string name = full_name.substr(1, full_name.size() - 6);
      string data = indices.first_child().value();
      result.push_back({name, data,});
    }
    return result;
  }

  void attach_vertex_group(Basic_Mesh &mesh, const string &data) {
    int count_index = 0;
    map<Vertex *, int> index_map;
//    vector<int> group_indices(mesh.vertices.size());
    for (int i = 0; i < mesh.vertices.size(); ++i) {
      int group = next_value<int>(data, count_index, atoi);
      int vertex_index = next_value<int>(data, count_index, atoi);
      index_map[mesh.vertices[vertex_index]] = group;
    }
    int index_buffer[8];

    for (auto polygon: mesh.polygons) {
      for (int i = 0; i < polygon->vertices.size(); ++i) {
        index_buffer[i] = index_map[polygon->vertices[i]];
      }
      polygon->set_data(sculptor::geometry::Vertex_Data::group, (float *) &index_buffer, 1, 1);
    }
  }


  void load_many_models(xml_node &collada, Mesh_Delegate delegate, bool loading_materials) {
    auto library = collada.child("library_geometries");
    auto controllers = collada.child("library_controllers");
    vector <Vertex_Group_Data> vertex_group_data;
    bool has_vertex_groups = false;
    if (!controllers.empty()) {
      vertex_group_data = load_vertex_groups(controllers);
      has_vertex_groups = true;
    }
    auto materials = loading_materials ? load_materials(collada) : map<const string, Material>();
    for (auto geometry : library.children("geometry")) {
      auto mesh = unique_ptr<Basic_Mesh>(new Basic_Mesh());
      load_geometry2(geometry, mesh.get(), [delegate, &mesh, &materials](Polygon *polygon, xml_node &polygon_list) {
        if (materials.size()) {
          auto material_id = polygon_list.attribute("material").value();
          auto material = &materials[material_id];
          polygon->set_data(Vertex_Data::color, (float *) &material->color, 0, 4);
        }
        mesh->add_polygon(polygon);
      });

      string name = geometry.attribute("name").value();

      if (has_vertex_groups) {
        for (auto &entry: vertex_group_data) {
          if (name == entry.mesh_name) {
            attach_vertex_group(*mesh, entry.data);
            break;
          }
        }
      }

      delegate(name, mesh);
    }
  }

  void load_geometry(xml_node &collada, Basic_Mesh *mesh, map<const string, Material> &materials) {
    auto library = collada.child("library_geometries");
    for (auto geometry : library.children("geometry")) {
      load_geometry2(geometry, mesh, [mesh, &materials](Polygon *polygon, xml_node &polygon_list) {
        auto material_id = polygon_list.attribute("material").value();
        auto material = &materials[material_id];
        polygon->set_data(Vertex_Data::color, (float *) &material->color, 0, 4);
        mesh->add_polygon(polygon);
      });
    }

  }

  void open_file(xml_document &document, const string &filename) {
#if ANDROID
    vector<char> buffer;
    android_load_binary(buffer, filename);
    xml_parse_result info = document.load_string((char*)buffer.data());
    if (!info)
      throw runtime_error(string("Error loading Collada file: ") + info.description());
#else
    xml_parse_result info = document.load_file(filename.c_str());
    if (!info)
      throw runtime_error(string("Error loading Collada file: ") + info.description());
#endif

  }

  unique_ptr <Basic_Mesh> load_collada_file(const string filename) {
    auto mesh = new Basic_Mesh();
    xml_document document;
    open_file(document, filename);
    auto collada = document.first_child();
    auto materials = load_materials(collada);
    load_geometry(collada, mesh, materials);
    return unique_ptr<Basic_Mesh>(mesh);
  }


  void load_collada_file(const string filename, Mesh_Delegate delegate, bool load_materials) {
    xml_document document;
    open_file(document, filename);
    auto collada = document.first_child();
    load_many_models(collada, delegate, load_materials);
  }
}