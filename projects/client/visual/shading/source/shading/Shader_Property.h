#pragma once

#include "commoner/dllexport.h"
#include "Program.h"
#include <string>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

using namespace glm;

namespace shading {

  class Effect;

  class Program;

  class MYTHIC_EXPORT Shader_Property {
  protected:
      const std::string name;
      int uniform_index;
      bool is_stale = true;
      Program &program;

  public:
      Shader_Property(const std::string &name, Program &program);
//      void set_matrix(const mat4 &value);
//      void set_vec4(float x, float y, float z, float w);

      inline const int &get_uniform_index() const {
        return uniform_index;
      }

      const string &get_name() const {
        return name;
      }

      virtual void refresh() = 0;
  };

  template<typename T, typename Functions>
  class Shader_Property_Template : public Shader_Property {
      T value;

  public:
      Shader_Property_Template(const std::string &name, Program &program) : Shader_Property(name, program) {}

      void set(const T &value) {
//        if (this->value == value)
//          return;


        if (program.is_active()) {
          if (get_uniform_index() != -1) {
            Functions::update(get_uniform_index(), value);
          }
        }
        else {
          is_stale = true;
          this->value = value;
        }
      }

      void refresh() {
        if (is_stale) {
          if (get_uniform_index() != -1) {
            Functions::update(get_uniform_index(), value);
          }
          is_stale = false;
        }
      }
  };

  struct MYTHIC_EXPORT Matrix_Property_Functions {
      static void update(unsigned int index, const mat4 &value);
  };

  class Matrix_Property : public Shader_Property_Template<mat4, Matrix_Property_Functions> {
  public:
      Matrix_Property(const std::string &name, Program &program) : Shader_Property_Template(name, program) {}
  };

  struct MYTHIC_EXPORT Vector4_Property_Functions {
      static void update(unsigned int index, const vec4 &value);
  };

  class Vector4_Property : public Shader_Property_Template<vec4, Vector4_Property_Functions> {
  public:
      Vector4_Property(const std::string &name, Program &program) : Shader_Property_Template(name, program) {}
//      void set(float x, float y, float z, float w) {
//        Shader_Property_Template::set(vec4(x, y, z, w));
//      }
  };

  struct MYTHIC_EXPORT Float_Property_Functions {
      static void update(unsigned int index, float value);
  };

  class Float_Property : public Shader_Property_Template<float, Float_Property_Functions> {
      float value;

  public:
      Float_Property(const std::string &name, Program &program) : Shader_Property_Template(name, program) {}
  };
}