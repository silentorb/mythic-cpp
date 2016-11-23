#include "Particle_Array.h"
#include "particular/visible/Visible_Particle.h"
#include "modeling/Vertex_Buffer.h"
#include <lookinglass/House.h>
#include <lookinglass/Lookinglass_Resources.h>
#include "Particle_Effect.h"
#include <shading/utility.h>

using namespace modeling;

namespace scenery {

  Particle_Array::Particle_Array(Particle_Effect &effect) :
    effect(effect),
    Spatial() {

    vertex_buffer = new Vertex_Buffer(effect.get_program().get_vertex_schema(), [&](int &vertex_count) {
      vertex_count = particles.size();
      return (float *) vertices.data();
    });

    lookinglass::House::get_instance().get_resources().add_resource(vertex_buffer);
  }

  Particle_Array::~Particle_Array() {
    lookinglass::House::get_instance().get_resources().remove_resource(vertex_buffer);
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

    effect.activate();
    shading::set_opacity_support(true);
    vertex_buffer->draw_points(particles.size());
  }

  void Particle_Array::add_particle(Visible_Particle *particle) {
    particles.push_back(unique_ptr<Visible_Particle>(particle));
    vertices.push_back(
      {
        particle->get_position(),
        particle->get_size(),
        particle->get_color()
      });
    changed = true;
  }

  void Particle_Array::remove_particle(Visible_Particle *particle) {
    for (int i = 0; i < particles.size(); ++i) {
      if (particles[i].get() == particle) {
        particles.erase(particles.begin() + i);
        vertices.erase(vertices.begin() + i);
        return;
      }
    }
    changed = true;
  }

  void Particle_Array::update(float delta) {
    Element::update(delta);
    int i = 0;
    for (auto &particle: particles) {
      particle->update(delta);
      auto &vertex = vertices[i++];
      vertex.color = particle->get_color();
      vertex.position = particle->get_position();
      vertex.scale = particle->get_size();
    }
  }

}