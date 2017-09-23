#pragma once

#include <bloom/flowers/Common_Flower.h>
#include <glm/vec4.hpp>
#include <bloom/flowers/Parent_Implementation.h>
#include <modeling/Simple_Mesh.h>
#include <bloom/flowers/Endpoint.h>

using namespace bloom;

namespace bloom {
  namespace flowers {

    class Border : public flowers::Common_Flower, public flowers::Endpoint {
        glm::vec4 color;
        float thickness;
        modeling::Simple_Mesh &mesh;
        modeling::Draw_Method draw_method = modeling::Draw_Method::line_loop;

    public:
        Border(const glm::vec4 &color, float thickness, flowers::Parent *parent = nullptr);
        Border(const glm::vec4 &color, float thickness, modeling::Simple_Mesh &mesh, modeling::Draw_Method draw_method,
               flowers::Parent *parent);

        virtual ~Border() override {

        }

        virtual void render() override;

        void set_color(glm::vec4 &color) {
          this->color = color;
        }

        void set_size(int value) {
          thickness = value;
        }

        virtual const string get_class_name() const override {
          return "Border";
        }
    };
  }
}