#include "string_additions.h"
#include <sstream>

namespace textual {

//  void string_replace(string &target, const string &pattern, const string &replacement) {
//    size_t position = 0;
//    while ((position = target.find(pattern, position)) != string::npos) {
//      target.replace(position, pattern.length(), replacement);
//      position += replacement.length();
//    }
//  }

  string string_replace(const string &source, const string &pattern, const string &replacement) {
    size_t position = 0;
    string result = source;
    while ((position = result.find(pattern, position)) != string::npos) {
      result.replace(position, pattern.length(), replacement);
      position += replacement.length();
    }

    return result;
  }

  vector<string> &split(const string &input, char delimiter, vector<string> &elements) {
    stringstream stream(input);
    string item;

    while (getline(stream, item, delimiter)) {
      elements.push_back(item);
    }

    return elements;
  }


  vector<string> split(const std::string &input, char delimiter) {
    vector<string> elements;
    split(input, delimiter, elements);
    return elements;
  }
}