#pragma once

//#include <regex>
//#include <functional>
#include <string>

using namespace std;

namespace textual {
//  string regex_replace(string text, regex pattern, function<string(smatch & )> action);
  string string_replace(string input, const string &pattern, const string &replacement);
}