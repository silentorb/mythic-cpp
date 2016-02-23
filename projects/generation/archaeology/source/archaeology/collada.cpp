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
  unique_ptr<Mesh> load_collada_file(const string filename) {
    auto mesh = new Mesh();
    xml_document document;

    xml_parse_result info = document.load_file(filename.c_str());
    if (!info)
      throw runtime_error(string("Error loading Collada file: ") + info.description());

//    auto collada = document.child("collada");
		auto collada = document.first_child();
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

        auto polygon_list = mesh_element.child("polylist");

				auto vcount = polygon_list.child("vcount");
        auto count_string = vcount.first_child().value();
        auto counts = textual::split(count_string, ' ');

				auto index_string = polygon_list.child("p").first_child().value();
				auto indices = textual::split(index_string, ' ');

        int step = 0;
        for (auto count_string : counts) {
          Selection polygon_vertices;
//          polygon_vertices.empty();
          int count = atoi(count_string.c_str());
          for (int i = 0; i < count; ++i) {
            int index = atoi(indices[step].c_str());
            step += 2;
            polygon_vertices.push_back(vertices[index]);
          }

					auto polygon = new Polygon(polygon_vertices);
//					polygon->flip();
          mesh->add_polygon(polygon);
        }
      }
    }

    return unique_ptr<Mesh>(mesh);
  }
}