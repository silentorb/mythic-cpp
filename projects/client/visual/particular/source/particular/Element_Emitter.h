#pragma once

#include <substance/Emitter.h>
#include "commoner/dllexport.h"
#include "scenery/elements/Group.h"
#include "Particle_Element.h"
#include "Particle_Array.h"

using namespace substance;

namespace scenery {

  typedef function<void(Particle_Element &)> Particle_Element_Delegate;

  class MYTHIC_EXPORT Element_Emitter : public scenery::Group, public substance::Particle_Listener {
  protected:
      unique_ptr<Emitter> emitter;
      Particle_Element_Delegate initializer;
      Particle_Element_Delegate animator;

  public:
      Element_Emitter(Emitter *emitter, Particle_Element_Delegate initializer, Parent *parent = nullptr);
      Element_Emitter(const Particle_Generator &generator, Particle_Element_Delegate initializer,
                      Particle_Element_Delegate animator, const Particle_Animator &particle_animator, Parent *parent);

      virtual void update(float delta) override;

      virtual void particle_added(const Particle &particle) override;

      virtual void particle_removed(const Particle &particle) override;

      Emitter &get_emitter() {
        return *emitter;
      }
  };
}