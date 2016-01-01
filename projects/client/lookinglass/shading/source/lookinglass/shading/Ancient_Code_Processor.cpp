#include "Ancient_Code_Processor.h"
#include <functional>
#include "textual/regex_additions.h"
#include <boost/regex.hpp>

using namespace textual;

namespace lookinglass {
	namespace shading {

		string olden(const string input, Shader_Type type) {
			string code = input;

			code = boost::regex_replace(code, boost::regex(R"(layout\s*\(.*?\)\s*uniform\s+(\w+)(\s*{.*?})\s*(\w+);)"), "struct $1 $2;\nuniform $1 $3;");
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
			}

			return code;
		}

		string Ancient_Code_Processor::process(Shader_Type type, const string source) {
			return string("precision highp float;\n\n") + olden(source, type);
		}
	}
}