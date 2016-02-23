#pragma once

#include "dllexport.h"
#include "Animation.h"
#include <vector>
#include <memory>

using namespace std;

namespace breeze {

  class MYTHIC_EXPORT Animation_Manager : no_copy {
      vector<unique_ptr<Animation>> animations;

  public:
      void update(float delta);
      void add_animation(Animation *animation);
  };
}