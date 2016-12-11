#pragma once

#include <substance/Emitter.h>
#include "scenery/elements/Group.h"
#include "particular/Particle_Element.h"
#include "particular/Particle_Array.h"

using namespace substance;

namespace scenery {

  typedef function<void(Visible_Particle &, float delta)> Particle_Point_Delegate;
  typedef function<Visible_Particle *(const Particle &)> Visible_Particle_Generator;

  class Point_Emitter_Bridge : public scenery::Spatial, public substance::Particle_Listener {
  protected:
      unique_ptr<Emitter> emitter;
      Visible_Particle_Generator visible_generator;
      Particle_Point_Delegate point_animator;
      Particle_Array *target_array;

  public:
      Point_Emitter_Bridge(Particle_Array *target_array, const Particle_Generator &generator,
                           Visible_Particle_Generator visible_generator, Particle_Point_Delegate point_animator,
                           const Particle_Animator &particle_animator);

      virtual ~Point_Emitter_Bridge();
      virtual void update(float delta) override;

      virtual void particle_added(const Particle &particle) override;

      virtual void particle_removed(const Particle &particle) override;

      Emitter &get_emitter() {
        return *emitter;
      }
  };
}