#pragma once

#include <aura/sequencing/Conductor.h>
#include <aura/music/composing/Composer.h>
#include "commoner/dllexport.h"
#include "Tempo_Loop.h"
#include "Performer.h"

namespace aura {

  class MYTHIC_EXPORT Producer {
      Composer &composer;
      Conductor &conductor;
      Engineer &engineer;
      unique_ptr<Performer> performer;
      unique_ptr<Tempo_Loop> chord_loop;

  public:
      Producer(Composer &composer, Conductor &conductor, Engineer &engineer);
      ~Producer();
      float update(float delta);
      void commence();

      Composer &get_composer() const {
        return composer;
      }

      Conductor &get_conductor() const {
        return conductor;
      }

      Engineer &get_engineer() const {
        return engineer;
      }

      Performer &get_performer() const {
        return *performer;
      }

      void next_section();
  };
}