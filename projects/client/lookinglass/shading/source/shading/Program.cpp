#include "Program.h"
#include "lookinglass/glow.h"
#include <string>
#include <stdexcept>
#include "logger.h"
#include "Shader_Manager.h"
#include "lookinglass/glow_gl.h"

namespace shading {

  Program *active_program = nullptr;

  Program::Program(const string name, Shader &first, Shader &second, initializer_list<string> names) :
    id(0), name(name), first(first), second(second), attribute_names(names), vertex_schema(nullptr) {
    load();
  }

  Program::Program(const string& name, const string &first, const string &second, const Vertex_Schema &vertex_schema) :
    id(0), name(name),
    first(Shader_Manager::get_instance().create_shader(Shader_Type::vertex, first)),
    second(Shader_Manager::get_instance().create_shader(Shader_Type::fragment, second)), vertex_schema(&vertex_schema) {
    for (auto& attribute: vertex_schema.get_attributes()) {
      attribute_names.push_back(attribute.get_name());
    }
    load();
		Shader_Manager::get_instance().register_program(this);
	}

  Program::Program(const string& name, Shader &first, Shader &second, const Vertex_Schema &vertex_schema) :
    id(0), name(name),
    first(first),
    second(second), vertex_schema(&vertex_schema) {
    for (auto& attribute: vertex_schema.get_attributes()) {
      attribute_names.push_back(attribute.get_name());
    }
    load();
    Shader_Manager::get_instance().register_program(this);
  }

  Program::~Program() {
      Shader_Manager::get_instance().unregister_program(*this);
    glDeleteProgram(id);
  }

  void Program::load() {
    if (id)
      return;

    id = glCreateProgram();
    glow::check_error("creating shader program");

    bind_attributes();
    log_info("Program %d, Shaders: %d, %d", id, first.id, second.id);
    log_info("Vertex code: %s", first.get_source_code().c_str());
    glAttachShader(id, first.id);
    glAttachShader(id, second.id);

    glLinkProgram(id);
    glow::check_error("linking shader program");

    GLint result = 1;
    glGetProgramiv(id, GL_LINK_STATUS, &result);
    if (result != GL_TRUE) {
      GLint message_length;
      glGetProgramiv(id, GL_INFO_LOG_LENGTH, &message_length);
      GLchar *message = new GLchar[message_length + 1];
      glGetProgramInfoLog(id, 255, &message_length, message);
      throw std::runtime_error(std::string("Failed to link shader code.  ") + message);
    }

    glValidateProgram(id);
    GLint validated = 1;
    glGetProgramiv(id, GL_VALIDATE_STATUS, &validated);
    if (validated == GL_FALSE)
      throw std::runtime_error("Shader program unable to run in current state.");
  }

  void Program::activate() {
    if (active_program != this) {
      glUseProgram(id);
      glow::check_error("set shader program");
      active_program = this;
    }
  }

  void Program::release() {
    if (!id)
      return;

    glDeleteProgram(id);
    id = 0;
  }

//    program->bind_attributes({"position", "normal", "color"});

  void Program::bind_attributes() {
    int index = 0;
    for (auto &attribute : attribute_names) {
      glBindAttribLocation(id, index++, attribute.c_str());
    }
  }
}
