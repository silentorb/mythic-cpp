#pragma once

#include <bloom/flowers/Common_Flower.h>
#include <glm/vec4.hpp>
#include <modeling/Simple_Mesh.h>
#include <bloom/flowers/Endpoint.h>

using namespace bloom;

namespace bloom {
  namespace flowers {

    class Fill : public flowers::Common_Flower, flowers::Endpoint {
        glm::vec4 color;
        modeling::Simple_Mesh &mesh;

    public:

        Fill(const glm::vec4 &color, flowers::Parent *parent = nullptr);
        Fill(const glm::vec4 &color, modeling::Simple_Mesh &mesh, flowers::Parent *parent = nullptr);

        virtual ~Fill() override {

        }

        virtual void render() override;

        void set_color(glm::vec4 value) {
          color = value;
        }

        glm::vec4 &get_color() {
          return color;
        }

        virtual const string get_class_name() const override {
          return "Fill";
        }

    };
  }
}