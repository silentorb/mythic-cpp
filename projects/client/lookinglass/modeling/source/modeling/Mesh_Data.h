#pragma once

#include "dllexport.h"
#include <memory>
#include "shading/Vertex_Schema.h"
#include "resourceful/Resource.h"
#include "Vertex_Buffer.h"
#include "Draw_Method.h"
#include <functional>

using namespace std;

namespace modeling {

  struct MYTHIC_EXPORT Mesh_Export {
      int polygon_count;
      int vertex_count;
      shared_ptr<float> vertices;
      shared_ptr<int> offsets;
      shared_ptr<int> counts;
      bool has_opacity;

      void initialize(int polygon_count, int vertex_count, float *vertices, int *offsets, int *counts, bool has_opacity = false) {
        this->polygon_count = polygon_count;
        this->vertex_count = vertex_count;
        this->vertices = shared_ptr<float>(vertices);
        this->offsets = shared_ptr<int>(offsets);
        this->counts = shared_ptr<int>(counts);
        this->has_opacity = has_opacity;
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
      unsigned int ebo = 0;
      int polygon_count;
//      int vertex_count;
      shared_ptr<int> offsets;
      shared_ptr<int> counts;
      Mesh_Data_Generator generator;
      bool support_lines;
      int index_count;
      bool _has_opacity;
      Vertex_Buffer vertex_buffer;

  public:

      Mesh_Data(Mesh_Data_Generator generator, Vertex_Schema &vertex_schema, bool support_lines = true, bool has_opacity = false);

      virtual ~Mesh_Data();

      const unsigned int &get_ebo() const {
        return ebo;
      }

      int get_polygon_count() const {
        return polygon_count;
      }

//      int get_vertex_count() const {
//        return vertex_count;
//      }

//      float *get_vertices() const {
//        return vertices.get();
//      }

      int *get_offsets() const {
        return offsets.get();
      }

      int *get_counts() const {
        return counts.get();
      }

//      unsigned int *get_indices() const {
//        return indices.get();
//      }

      virtual void release() override;
      virtual void load() override;

      bool supports_lines() const {
        return support_lines;
      }

      int get_indexed_triangle_count() const {
        return index_count / 3;
      }

      int get_index_count() const {
        return index_count;
      }

      bool has_opacity() const {
        return _has_opacity;
      }

      void draw(Draw_Method draw_method);
  };

}
