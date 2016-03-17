#pragma once

#include <substance/Emitter.h>
#include "dllexport.h"
#include "Group.h"
#include "Particle_Element.h"

using namespace substance;

namespace scenery {

  typedef function<void(Particle_Element &)> Particle_Element_Delegate;

  class MYTHIC_EXPORT Emitter_Element : public scenery::Group, public substance::Particle_Listener {
  protected:
      unique_ptr<Emitter> emitter;
      Particle_Element_Delegate initializer;

  public:
      Emitter_Element(Emitter *emitter, Particle_Element_Delegate initializer, Parent *parent = nullptr);
      Emitter_Element(const Particle_Generator &generator, Particle_Element_Delegate initializer, Parent *parent);

      virtual void update(float delta) override;

      virtual void particle_added(Particle &particle) override;

      virtual void particle_removed(Particle &particle) override;

      Emitter &get_emitter() {
        return *emitter;
      }
  };
}