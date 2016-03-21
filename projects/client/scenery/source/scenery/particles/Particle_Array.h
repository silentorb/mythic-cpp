#pragma once

#include "scenery/elements/Element.h"
#include <vector>

namespace substance {
  class Particle;
}

namespace scenery {

  class MYTHIC_EXPORT Particle_Array : public scenery::Element {
      vector<substance::Particle> particles;
      unsigned int vao;
      unsigned int vbo;

  public:
      Particle_Array(Parent *parent);

      virtual void render() override;


  };
}