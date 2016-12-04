#include "Version.h"
#include "glow.h"
#include <regex>
#include <string>
#include "glow_gl.h"

using namespace std;

namespace glow {

  void parse_version_text(char *text, string values[2]) {
    auto i = 0;
    auto mode = 0;

    while (auto current = text[i++]) {
      switch (mode) {
        case 0:
          if (current >= '0' && current <= '9') {
            values[0] = current;
            mode = 1;
          }
          break;

        case 1:
          if (current >= '0' && current <= '9') {
            values[0] += current;
          }
          else if (current == '.') {
            mode = 2;
          }
          else {
            mode = 0;
          }
          break;

        case 2:
          if (current >= '0' && current <= '9') {
            values[1] = current;
            mode = 3;
          }
          break;

        case 3:
          if (current >= '0' && current <= '9') {
            values[1] += current;
          }
          else {
            return;
          }
          break;
      }
    }

    if (mode != 3)
      throw string("Could not parse OpenGL version text '") + text + "'";
  }

  Version::Version() {
    auto text = (char *) glGetString(GL_VERSION);
    string values[2];
    parse_version_text(text, values);
    major = values[0][0] - '0';
    minor = values[1][0] - '0';

//      major = stoi(values[0]);
//      minor = stoi(values[1]);
//      regex pattern{R"(\d+)\.(\d+)"};
//
    smatch matches;
//      if (!regex_match(text, matches, pattern))
//        throw "Could not determine OpenGL version";
//
//      major = stoi(matches[0]);
//      minor = stoi(matches[1]);
  }

  Version::Version(int major, int minor) :
    major(major), minor(minor) {
    ES = false;
  }

  bool Version::at_least(int major, int minor) {
    return this->major > major
           || (this->major == major && this->minor >= minor);
  }
}

/*
 //        if (current >= '0' && current <= '9' && (mode == 0 || ) {
//          auto current_value = mode == 1 ? 0 : 1;
//          values[current_value] = values[current_value] + current;
//          if (mode == 0)
//            mode = 1;
//          else if (mode == 2)
//            mode = 3;
//        }
//        else if (current == '.' && mode == 1) {
//          mode == 2;
//        }
//        else if (mode == 2) {
//          break;
//        }
//        else if (mode != 0) {
//          mode == 0;
//          values[0] = '';
//          values[1] = '';
//        }
//      }
 */