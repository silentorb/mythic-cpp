#include "Particle_Array.h"
#include "Pretty_Particle.h"
#include "modeling/Vertex_Buffer.h"
#include <lookinglass/House.h>
#include <lookinglass/Lookinglass_Resources.h>
#include "Particle_Effect.h"
#include <shading/utility.h>

using namespace modeling;

namespace scenery {

  Particle_Array::Particle_Array(shared_ptr<Particle_Effect> effect, Parent *parent) :
    effect(effect),
    Element(parent) {

    vertex_buffer = unique_ptr<Vertex_Buffer>(new Vertex_Buffer(effect->get_vertex_schema(), [&](int &vertex_count) {
      vertex_count = particles.size();
      return (float *) vertices.data();
    }));

    lookinglass::House::get_instance().get_resources().add_resource(vertex_buffer.get());
  }

  Particle_Array::~Particle_Array() {
    lookinglass::House::get_instance().get_resources().remove_resource(vertex_buffer.get());
  }

//  float *Particle_Array::generate(int &vertex_count) {
//    vertex_count = particles.size();
//    return static_cast<float*>(data.data());
//  }

  void Particle_Array::render() {
    if (changed) {
      changed = false;
      vertex_buffer->load();
    }

    effect->activate();
    shading::set_opacity_support(true);
    vertex_buffer->draw_points(particles.size());
  }

  void Particle_Array::add_particle(Pretty_Particle *particle) {
    particles.push_back(unique_ptr<Pretty_Particle>(particle));
    vertices.push_back(
      {
        particle->get_position(),
        particle->get_size(),
        particle->get_color()
      });
  }

  void Particle_Array::remove_particle(Pretty_Particle *particle) {
    for (int i = 0; i < particles.size(); ++i) {
      if (particles[i].get() == particle) {
        particles.erase(particles.begin() + i);
        vertices.erase(vertices.begin() + i);
        return;
      }
    }
  }
}