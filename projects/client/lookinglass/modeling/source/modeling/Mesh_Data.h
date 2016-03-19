#pragma once

#include "dllexport.h"
#include <memory>
#include "Vertex_Schema.h"
#include "resourceful/Resource.h"

using namespace std;

namespace modeling {

  struct MYTHIC_EXPORT Mesh_Export {
      int polygon_count;
      int vertex_count;
      shared_ptr<float> vertices;
      shared_ptr<int>offsets;
      shared_ptr<int>counts;

      void initialize(int polygon_count, int vertex_count, float *vertices, int *offsets, int *counts) {
        this->polygon_count = polygon_count;
        this->vertex_count = vertex_count;
        this->vertices = shared_ptr<float>(vertices);
        this->offsets = shared_ptr<int>(offsets);
        this->counts = shared_ptr<int>(counts);
      }

//      Mesh_Export(const Mesh_Export &other) {
//        intitialize(
//          other.polygon_count,
//          other.vertex_count,
//          vertices_buffer,
//          other.offsets,
//          other.counts
//        );
//      }
  };

  typedef function<void(Mesh_Export &data)> Mesh_Data_Generator;

  class MYTHIC_EXPORT Mesh_Data : public resourceful::Resource {
  private:
      unsigned int vao;
      unsigned int vbo;
      int polygon_count;
      int vertex_count;
      shared_ptr<int> offsets;
      shared_ptr<int> counts;
      shared_ptr<int> indices;
      Vertex_Schema &vertex_schema;
      Mesh_Data_Generator generator;

  public:

      Mesh_Data(Mesh_Data_Generator generator, Vertex_Schema &vertex_schema);

      ~Mesh_Data();

      unsigned int get_vao() const {
        return vao;
      }

      int get_polygon_count() const {
        return polygon_count;
      }

      int get_vertex_count() const {
        return vertex_count;
      }

//      float *get_vertices() const {
//        return vertices.get();
//      }

      int *get_offsets() const {
        return offsets.get();
      }

      int *get_counts() const {
        return counts.get();
      }

      int *get_indices() const {
        return indices.get();
      }

      virtual void free() override;
      virtual void load() override;
  };

}
