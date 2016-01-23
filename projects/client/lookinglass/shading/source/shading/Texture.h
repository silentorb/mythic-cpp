#pragma once

#include "resourceful/Resource.h"
#include "Texture_Generator.h"
#include <memory>

using namespace std;

namespace shading {

  class Texture : public resourceful::Resource {
      unsigned int id;
      int width, height;
      unique_ptr<Texture_Generator> generator;

  public:
      Texture(int width, int height, Texture_Generator *generator);

      virtual void free() override;
      virtual void load() override;

      void activate();
  };
}
