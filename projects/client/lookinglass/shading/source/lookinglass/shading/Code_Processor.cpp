#include "Code_Processor.h"
#include <regex>
#include <functional>

namespace lookinglass {
	namespace shading {

		string regex_replace(string text, regex pattern, function<string(smatch &)> action) {
			string result = text;
			smatch match;
			string next = result;
			int i = 0;
			while (regex_search(next, match, pattern)) {
				auto replacement = action(match);
				int start = match.position();
				int end = start + match[0].length();
				result = result.substr(0, start) + replacement +
					result.substr(end);
				i += replacement.size();
				next = result.substr(i);
			}

			return result;
		}

		Code_Processor::Code_Processor(Shader_Loader &shader_loader)
			: shader_loader(shader_loader) {
		}

		string Code_Processor::process(Shader_Type type, const string source) {
			return string("#version ") + "440" + "\n" + process_includes(type, source);
		}

		string Code_Processor::process_includes(Shader_Type type, const string source) {
			static regex include_pattern{ R"(#include\s*<([\w/]+)>)" };
			auto action = [&](smatch &match) { return shader_loader.load((string)match[1]); };
			return regex_replace(source, include_pattern, action);
		}
	}
}