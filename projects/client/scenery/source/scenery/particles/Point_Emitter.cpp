#include <glm/gtc/matrix_transform.hpp>
#include "Point_Emitter.h"
#include "Particle_Element.h"

namespace scenery {

//  Point_Emitter::Point_Emitter(Emitter *emitter, Particle_Element_Delegate initializer, Parent *parent) :
//    emitter(emitter), initializer(initializer), scenery::Group(parent) {
//
//  }

  Point_Emitter::Point_Emitter(
    const Particle_Generator &generator, Particle_Point_Delegate initializer,
    Particle_Point_Delegate animator, Parent *parent) :
    emitter(new Emitter(generator, this)), initializer(initializer), animator(animator), scenery::Group(parent) {

  }

  void Point_Emitter::update(float delta) {
    auto absolute_position = vec3(get_transform() * vec4(vec3(0), 1));
    emitter->set_position(absolute_position);
    emitter->update(delta);
    for (auto &element: children) {
      auto particle_element = static_cast<Particle_Element *>(element.get());
      animator(*particle_element);
    }
  }

  void Point_Emitter::particle_added(Particle &particle) {
    auto child = new Particle_Element(particle, this);
    initializer(*child);
  }

  void Point_Emitter::particle_removed(Particle &particle) {
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