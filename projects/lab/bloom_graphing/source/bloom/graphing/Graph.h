#pragma once

#include <bloom/flowers/Common_Flower.h>
#include <bloom/flowers/Endpoint.h>
#include <functional>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace modeling {
  class Simple_Mesh;
}

namespace bloom {
  namespace graphing {

    class Graph : public flowers::Common_Flower, public flowers::Endpoint {
        std::unique_ptr<modeling::Simple_Mesh> mesh;
        std::vector<glm::vec2> points;
        glm::vec2 minimum_range;
        glm::vec2 maximum_range;

        // This is temporary until generating shaders is streamlined and this library can define a custom shader
        // in code without copying a GLSL resource file.  It would be simpler not to need to include color in
        // the vec
        struct Colored_Point {
            glm::vec2 position;
            glm::vec4 color;

            Colored_Point(const glm::vec2 &position, const glm::vec4 &color) : position(position), color(color) {}
        };

        std::vector<Colored_Point> colored_points;

        void initialize_colored_points();

    public:
        Graph();

        template<typename Iterable>
        void add_points(const Iterable &iterable) {
          points.clear();

          for (auto &point : iterable) {
            points.push_back(point);
          }
          initialize_colored_points();
        }

        template<typename Iterable, typename Item_Type>
        void add_points(const Iterable &iterable, const std::function<glm::vec2(const Item_Type &)> &converter) {
          points.clear();

          for (auto &point : iterable) {
            points.push_back(converter(point));
          }
          initialize_colored_points();
        }

        void render() override;

        void set_minimum_range(const glm::vec2 &value) {
          minimum_range = value;
        }

        void set_maximum_range(const glm::vec2 &value) {
          maximum_range = value;
        }
    };
  }
}