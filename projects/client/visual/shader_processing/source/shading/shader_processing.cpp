#include "shader_processing.h"
#include "textual/regex_additions.h"
#include <boost/regex.hpp>
#include <glow/Capabilities.h>

using namespace textual;

namespace shading {

  const string process_includes(const string &source, Shader_Type type, resourceful::File_Loader file_loader) {
    static boost::regex include_pattern{R"(#include\s*<([\w/]+)>)"};
    auto action = [&](const boost::smatch &match) { return file_loader("shaders/" + (string) match[1] + ".glsl"); };
    return boost::regex_replace(source, include_pattern, action);
  }

  const string olden(const string &input, Shader_Type type) {
    string code = input;

//			code = boost::regex_replace(code, boost::regex(R"(layout\s*\(.*?\)\s*uniform\s+(\w+)(\s*{.*?})\s*(\w+);)"), "struct $1 $2;\nuniform $1 $3;");
    code = boost::regex_replace(code, boost::regex(R"(layout\s*\(.*?\)\s*)"), "");
    if (type == Shader_Type::vertex) {
      code = boost::regex_replace(code, boost::regex(R"(^\s*in\s)"), "attribute ");
      code = boost::regex_replace(code, boost::regex(R"(^\s*out\s)"), "varying ");
    }
    else {
      code = boost::regex_replace(code, boost::regex(R"(^\s*in\s)"), "varying ");
      code = string_replace(code, "out vec4 output_color;", "");
      code = string_replace(code, "output_color", "gl_FragColor");
      code = boost::regex_replace(code, boost::regex(R"(texture\s*\()"), "texture2D(");
      if (!glow:: Capabilities:: get_instance().multisamplers()) {
        code = string_replace(code, "sampler2DMS", "sampler2D");
      }
    }

    return code;
  }
}