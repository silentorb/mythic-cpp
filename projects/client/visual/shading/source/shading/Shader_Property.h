#pragma once

#include "Program.h"
#include <string>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

using namespace glm;

namespace shading {

  class Effect;

  class Program;

  class Shader_Property {
  protected:
      const std::string name;
      int uniform_index;
      bool is_stale = true;
      bool is_initialized = false;
      Program &program;

  public:
      Shader_Property(const std::string &name, Program &program);

      inline const int &get_uniform_index() const {
        return uniform_index;
      }

      const string &get_name() const {
        return name;
      }

      virtual void refresh() = 0;
  };

  template<typename T, typename Functions, int Count>
  class Shader_Property_Template : public Shader_Property {
      T value[Count];

  public:
      Shader_Property_Template(const std::string &name, Program &program) : Shader_Property(name, program) {}

      void set(const T &value) {
        if (is_initialized && this->value[0] == value)
          return;

        is_initialized = true;
        this->value[0] = value;

        if (program.is_active()) {
          if (get_uniform_index() != -1) {
            Functions::update(get_uniform_index(), &value, 1);
          }
        }
        else {
          is_stale = true;
        }
      }

      void refresh() {
        if (is_stale) {
          if (get_uniform_index() != -1) {
            Functions::update(get_uniform_index(), &value[0], 1);
          }
          is_stale = false;
        }
      }

      void set(const T *values, int count) {
        if (program.is_active()) {
          if (get_uniform_index() != -1) {
            Functions::update(get_uniform_index(), values, count);
          }
        }
        else {
//          is_stale = true;
//          this->value = value;
        }
      }
  };

  struct  Matrix_Property_Functions {
      static void update(unsigned int index, const mat4 *values, int count);
  };

  class Matrix_Property : public Shader_Property_Template<mat4, Matrix_Property_Functions, 1> {
  public:
      Matrix_Property(const std::string &name, Program &program) : Shader_Property_Template(name, program) {}
  };

  template<int Count>
  class Matrix_Property_Array : public Shader_Property_Template<mat4, Matrix_Property_Functions, Count> {
  public:
      Matrix_Property_Array(const std::string &name, Program &program) :
        Shader_Property_Template<mat4, Matrix_Property_Functions, Count>(name, program) {}
  };

  struct Vector4_Property_Functions {
      static void update(unsigned int index, const vec4 *values, int count);
  };

  class Vector4_Property : public Shader_Property_Template<vec4, Vector4_Property_Functions, 1> {
  public:
      Vector4_Property(const std::string &name, Program &program) : Shader_Property_Template(name, program) {}
  };

  struct Vector2_Property_Functions {
      static void update(unsigned int index, const vec2 *values, int count);
  };

  class Vector2_Property : public Shader_Property_Template<glm::vec2, Vector2_Property_Functions, 1> {
  public:
      Vector2_Property(const std::string &name, Program &program) : Shader_Property_Template(name, program) {}
  };

  struct Float_Property_Functions {
      static void update(unsigned int index, const float *values, int count);
  };

  class Float_Property : public Shader_Property_Template<float, Float_Property_Functions, 1> {
  public:
      Float_Property(const std::string &name, Program &program) : Shader_Property_Template(name, program) {}
  };
}