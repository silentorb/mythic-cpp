#pragma once

#include "scenery/elements/Element.h"
#include "Particle_Effect.h"
#include <vector>
#include <memory>

namespace shading {
  class Vertex_Schema;
}

namespace modeling {
  class Vertex_Buffer;
}

namespace scenery {

  class Particle_Effect;

  class Pretty_Particle;

  struct Particle_Data {
      vec3 position;
      float scale;
      vec4 color;
  };

  class MYTHIC_EXPORT Particle_Array : public scenery::Element {
      bool changed = true;
      vector<unique_ptr<Pretty_Particle>> particles;
      vector<Particle_Data> vertices;
      unique_ptr<modeling::Vertex_Buffer> vertex_buffer;
      shared_ptr<Particle_Effect> effect;

//      float* generate(int & vertex_count);

  public:
      Particle_Array(shared_ptr<Particle_Effect> effect, Parent *parent = nullptr);
      ~Particle_Array();

      virtual void render() override;
      void add_particle(Pretty_Particle *particle);
      void remove_particle(Pretty_Particle *particle);
  };
}