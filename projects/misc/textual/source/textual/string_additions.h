#pragma once

#include <commoner/dllexport.h>
#include <string>
#include <vector>

using namespace std;

namespace textual {

//  void string_replace(string &target, const string &pattern, const string &replacement);
  MYTHIC_EXPORT string string_replace(const string &source, const string &pattern, const string &replacement);
  MYTHIC_EXPORT void split(const string &input, char delimiter, vector<string> &elements);
  MYTHIC_EXPORT vector<string> split(const string &input, char delimiter);
}