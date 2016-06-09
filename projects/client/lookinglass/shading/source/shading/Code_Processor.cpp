#include "Code_Processor.h"
#include <functional>
#include "textual/regex_additions.h"
#include <boost/regex.hpp>

using namespace textual;

namespace shading {


//  Code_Processor::Code_Processor(Shader_Loader &shader_loader)
//    : shader_loader(shader_loader) {
//  }
//
//  string Code_Processor::process(Shader_Type type, const string source) {
//    return string("#version ") + "440" + "\n" + process_includes(source, type);
//  }
//
//  string Code_Processor::process_includes(const string source, Shader_Type type) {
//    static boost::regex include_pattern{R"(#include\s*<([\w/]+)>)"};
//    auto action = [&](const boost::smatch &match) { return shader_loader.load((string) match[1]); };
//    return boost::regex_replace(source, include_pattern, action);
//  }
}
