//#pragma once
//
//#include <substance/Emitter.h>
//#include "dllexport.h"
//#include "scenery/elements/Group.h"
//#include "Particle_Element.h"
//#include "Particle_Array.h"
//
//using namespace substance;
//
//namespace scenery {
//
//  typedef function<void(Particle &)> Particle_Point_Delegate;
//
//  class MYTHIC_EXPORT Point_Emitter : public scenery::Group, public substance::Particle_Listener {
//  protected:
//      unique_ptr<Emitter> emitter;
//      Particle_Point_Delegate initializer;
//      Particle_Point_Delegate animator;
//      Particle_Array container;
//
//  public:
////      Point_Emitter(Emitter *emitter, Particle_Point_Delegate initializer, Parent *parent = nullptr);
//      Point_Emitter(const Particle_Generator &generator, Particle_Point_Delegate initializer, Particle_Point_Delegate animator, Parent *parent);
//
//      virtual void update(float delta) override;
//
//      virtual void particle_added(Particle &particle) override;
//
//      virtual void particle_removed(Particle &particle) override;
//
//      Emitter &get_emitter() {
//        return *emitter;
//      }
//  };
//}