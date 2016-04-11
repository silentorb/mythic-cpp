#pragma once

#include <aura/sequencing/Conductor.h>
#include <aura/music/composing/Composer.h>
#include "dllexport.h"
#include "Tempo_Loop.h"

namespace aura {

  class MYTHIC_EXPORT Producer {
      Composer &composer;
      Conductor &conductor;
      unique_ptr<Tempo_Loop> chord_loop;

  public:
      Producer(Composer &composer, Conductor &conductor, Engineer & engineer);
      void update();
  };
}