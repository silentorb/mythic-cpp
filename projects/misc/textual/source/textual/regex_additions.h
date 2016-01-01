#pragma once

//#include <regex>
//#include <functional>
#include <string>
#include <dllexport.h>

using namespace std;

namespace textual {
//  MYTHIC_EXPORT string regex_replace(string text, regex pattern, function<string(smatch & )> action);
  MYTHIC_EXPORT string string_replace(string input, const string &pattern, const string &replacement);
}