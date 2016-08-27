#include <glm/gtc/matrix_transform.hpp>
#include "Point_Emitter_Bridge.h"
#include "particular/visible/Visible_Particle.h"

namespace scenery {

  Point_Emitter_Bridge::Point_Emitter_Bridge(
    Particle_Array *target_array,
    const Particle_Generator &generator, Visible_Particle_Generator visible_generator,
    Particle_Point_Delegate animator, Parent *parent) :
    target_array(target_array),
    emitter(new Emitter(generator, this)), visible_generator(visible_generator), animator(animator),
    scenery::Spatial(parent) {

  }

  void Point_Emitter_Bridge::update(float delta) {
    auto absolute_position = vec3(get_transform() * vec4(vec3(0), 1));
    emitter->set_position(absolute_position);
    emitter->update(delta);
    target_array->set_changed();
  }

  void Point_Emitter_Bridge::particle_added(const Particle &particle) {
    auto child = visible_generator(particle);
    child->set_animator(animator);
    target_array->add_particle(child);
    child->update(0);
  }

  void Point_Emitter_Bridge::particle_removed(const Particle &particle) {
    auto &points = target_array->get_particles();
    for (int i = points.size() - 1; i >= 0; --i) {
      auto &child = points[i];
      if (child->get_particle() == &particle) {
        target_array->remove_particle(child.get());
        return;
      }
    }

    throw runtime_error("Could not find particle element to remove.  Particle element unaccounted for.");
  }
}