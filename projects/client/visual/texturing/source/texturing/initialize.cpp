#include "initialize.h"

using namespace shading;

const char *_image_vertex = R"HEREDOC(
#version 440
in vec4 vertex;
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 transform;

void main()
{
    vec4 temp = transform * vec4(vertex.xy, 0.0, 1.0);
    gl_Position = vec4(temp.x / 500.0 - 1.0, (1000.0 - temp.y) / 500.0 - 1.0, 0.0, 1);
 //    gl_Position = projection * transform * vec4(vertex.xy, 0.0, 1.0);
   TexCoords = vertex.zw;
}

)HEREDOC";

const char *_image_fragment = R"HEREDOC(
#version 440
in vec2 TexCoords;
out vec4 output_color;

uniform sampler2D text;

void main()
{
    output_color = texture(text, TexCoords);
}
)HEREDOC";

const char *_colored_image_fragment = R"HEREDOC(
#version 440
in vec2 TexCoords;
out vec4 output_color;

uniform sampler2D text;
uniform vec4 color;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    output_color = color * sampled;
}
)HEREDOC";

namespace texturing {

  void initialize_texture_shaders(Shader_Manager &shader_manager) {
    static bool initialized = false;
    if (initialized)
      return;

    initialized = true;

    auto &image_vertex = shader_manager.create_shader(Shader_Type::vertex, string(_image_vertex));

    shader_manager.create_program("image",
                                  image_vertex,
                                  shader_manager.create_shader(Shader_Type::fragment, string(_image_fragment)), {});

    shader_manager.create_program("colored-image",
                                  image_vertex,
                                  shader_manager.create_shader(Shader_Type::fragment, string(_colored_image_fragment)),
                                  {});
  }
}
