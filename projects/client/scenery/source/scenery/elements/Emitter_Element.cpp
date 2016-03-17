#include <glm/gtc/matrix_transform.hpp>
#include "Emitter_Element.h"
#include "Particle_Element.h"

namespace scenery {

  Emitter_Element::Emitter_Element(Emitter *emitter, Particle_Element_Delegate initializer, Parent *parent) :
    emitter(emitter), initializer(initializer), Group(parent) {

  }

  Emitter_Element::Emitter_Element(
    const Particle_Generator &generator, Particle_Element_Delegate initializer, Parent *parent) :
    emitter(new Emitter(generator, this)), initializer(initializer), Group(parent) {

  }

  void Emitter_Element::update(float delta) {
		auto absolute_position = vec3(get_transform() * vec4(vec3(0), 1));
    emitter->set_position(absolute_position);
    emitter->update(delta);
    Group::update(delta);
  }

  void Emitter_Element::particle_added(Particle &particle) {
    auto child = new Particle_Element(particle, this);
    initializer(*child);
  }

  void Emitter_Element::particle_removed(Particle &particle) {
    for (int i = 0; i < children.size(); ++i) {
      auto child = static_cast<Particle_Element *>(children[i].get());
      if (&child->get_particle() == &particle) {
        child->remove();
        return;
      }
    }

		throw runtime_error("Could not find particle element to remove.  Particle element unaccounted for.");
  }
}