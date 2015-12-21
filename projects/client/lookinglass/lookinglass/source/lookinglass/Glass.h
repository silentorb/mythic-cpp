#pragma once

#include <string>

using namespace std;

struct SDL_Window;

namespace lookinglass {
  class Glass {
  public:

      Glass(const char *title);

      virtual ~Glass() { }

  private:

  };

}

