#pragma once

#include "scenery/elements/Spatial.h"
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

  class Visible_Particle;

  struct Particle_Data {
      vec3 position;
      float scale;
      vec4 color;
  };

  class Particle_Array : public scenery::Spatial {
      bool changed = true;
      vector<unique_ptr<Visible_Particle>> particles;
      vector<Particle_Data> vertices;
      modeling::Vertex_Buffer* vertex_buffer;
      Particle_Effect& effect;

//      float* generate(int & vertex_count);

  public:
      virtual void update(float delta) override;
      Particle_Array(Particle_Effect &effect);
      ~Particle_Array();

      virtual void render() override;
      void add_particle(Visible_Particle *particle);
      void remove_particle(Visible_Particle *particle);

      const vector<unique_ptr<Visible_Particle>> &get_particles() const {
        return particles;
      }

      void set_changed() {
        changed = true;
      }
  };
}