#pragma once

#include "dllexport.h"

#include "declarations.h"
#include <map>
#include <string>

namespace sculptor {
  namespace geometry {

    struct Vertex_Data {
        int id;
        vector<float> values;

        enum common_ids {
            position = 1,
            normal,
            uv,
            color
        };
    };

    class MYTHIC_EXPORT Polygon {
    private:
        void initialize();
        void add_vertex(Vertex *vertex);
        vector<Vertex_Data> data;
        vec3 normal;
        vector<Edge *> edges;

        void initialize_edges();

    public:
        vector<Basic_Mesh *> meshes;
        vector<Vertex *> vertices;
        vector<Edge *> get_edges();

        Polygon(initializer_list<Vertex *>);
        Polygon(const Selection &selection);
        Polygon(Vertex *first, Vertex *second, Vertex *third, Vertex *fourth);
        Polygon(Vertex *first, Vertex *second, Vertex *third);
        ~Polygon();

        void remove();

        vec3 calculate_normal() const;

        void set_data(int id, float *data, int step, int count);

        float *get_data(int id) {
          for (auto &entry: data) {
            if (entry.id == id)
              return entry.values.data();
          }
          return nullptr;
        }

        Vertex_Data *get_entry(int id) {
          for (auto &entry: data) {
            if (entry.id == id)
              return &entry;
          }
          return nullptr;
        }

        float *get_data(int id, int index) {
          auto entry = get_entry(id);
          if (!entry)
            return nullptr;

          auto step = entry->values.size() / vertices.size();
          return entry->values.data() + index * step;
        }

        const vec3 &get_normal() const {
          return normal;
        }

        void set_normal(const vec3 &normal) {
          Polygon::normal = normal;
        }

        vec3 get_center() const;

        const vector<int> get_indices(const Selection &selection) const;

        void flip();
    };
  }
}
