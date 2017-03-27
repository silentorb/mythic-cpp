#pragma once

#include <string>
#include <vector>

using namespace std;

namespace textual {

//  void string_replace(string &target, const string &pattern, const string &replacement);
  string string_replace(const string &source, const string &pattern, const string &replacement);
  void split(const string &input, char delimiter, vector<string> &elements);
  vector<string> split(const string &input, char delimiter);
}