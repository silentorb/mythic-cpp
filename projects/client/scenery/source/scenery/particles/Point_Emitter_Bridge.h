#pragma once

#include <substance/Emitter.h>
#include "dllexport.h"
#include "scenery/elements/Group.h"
#include "scenery/particles/Particle_Element.h"
#include "scenery/particles/Particle_Array.h"

using namespace substance;

namespace scenery {

  typedef function<void(Visible_Particle &)> Particle_Point_Delegate;
  typedef function<Visible_Particle *(const Particle &)> Visible_Particle_Generator;

  class MYTHIC_EXPORT Point_Emitter_Bridge : public scenery::Element, public substance::Particle_Listener {
  protected:
      unique_ptr<Emitter> emitter;
      Visible_Particle_Generator visible_generator;
      Particle_Point_Delegate animator;
      Particle_Array *target_array;

  public:
      Point_Emitter_Bridge(Particle_Array *target_array, const Particle_Generator &generator,
                           Visible_Particle_Generator visible_generator, Particle_Point_Delegate animator, Parent *parent);

      virtual void update(float delta) override;

      virtual void particle_added(const Particle &particle) override;

      virtual void particle_removed(const Particle &particle) override;

      Emitter &get_emitter() {
        return *emitter;
      }
  };
}