#include <glm/gtc/matrix_transform.hpp>
#include "Element_Emitter.h"
#include "Particle_Element.h"

namespace scenery {

  Element_Emitter::Element_Emitter(Emitter *emitter, Particle_Element_Delegate initializer) :
    emitter(emitter), initializer(initializer), scenery::Group() {

  }

  Element_Emitter::Element_Emitter(
    const Particle_Generator &generator, Particle_Element_Delegate initializer,
    Particle_Element_Delegate animator, const Particle_Animator &particle_animator) :
    emitter(new Emitter(generator, this, particle_animator)), initializer(initializer), animator(animator),
    scenery::Group() {

  }

  void Element_Emitter::update(float delta) {
    auto absolute_position = vec3(get_transform() * vec4(vec3(0), 1));
    emitter->set_position(absolute_position);
    emitter->update(delta);
    for (auto &element: children) {
      auto particle_element = (Particle_Element *)(void*) element.get();
      animator(*particle_element);
    }
  }

  void Element_Emitter::particle_added(const Particle &particle) {
    auto child = new Particle_Element(particle, this);
    initializer(*child);
  }

  void Element_Emitter::particle_removed(const Particle &particle) {
    for (int i = 0; i < children.size(); ++i) {
      auto child = (Particle_Element *)(void*)(children[i].get());
      if (&child->get_particle() == &particle) {
        child->remove();
        return;
      }
    }

    throw runtime_error("Could not find particle element to remove.  Particle element unaccounted for.");
  }
}