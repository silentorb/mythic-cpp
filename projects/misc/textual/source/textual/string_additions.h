#pragma once

#include <dllexport.h>
#include <string>

using namespace std;

namespace textual {

//  void string_replace(string &target, const string &pattern, const string &replacement);
 MYTHIC_EXPORT string string_replace(const string &source, const string &pattern, const string &replacement);
}