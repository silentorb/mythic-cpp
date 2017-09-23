#include "regex_additions.h"

namespace textual {

//  string regex_replace(string text, regex pattern, function<string(smatch & )> action) {
//    string result = text;
//    smatch match;
//    string next = result;
//    int i = 0;
//    while (regex_search(next, match, pattern)) {
//      auto replacement = action(match);
//      int start = match.position();
//      int end = start + match[0].length();
//      result = result.substr(0, start) + replacement +
//               result.substr(end);
//      i += replacement.size();
//      next = result.substr(i);
//    }
//
//    return result;
//  }

	string string_replace(string input, const string& pattern, const string& replacement) {
		size_t start = 0;
		while ((start = input.find(pattern, start)) != string::npos) {
			input.replace(start, pattern.length(), replacement);
			start += replacement.length();
		}

		return input;
	}
}