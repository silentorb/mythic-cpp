#pragma once

#include <aura/sequencing/Conductor.h>
#include <aura/composing/Composer.h>
#include <aura/performance/Performance_Producer.h>
#include "aura/performance/Tempo_Loop.h"
#include "aura/performance/Musical_Performer.h"

namespace aura {
  namespace producing {

    class Producer : virtual public performing::Performance_Producer {
        Composer &composer;
        Conductor &conductor;
        engineering::Engineer &engineer;
        unique_ptr<performing::Musical_Performer> performer;
        unique_ptr<performing::Tempo_Loop> chord_loop;

    public:
        Producer(Composer &composer, Conductor &conductor, engineering::Engineer &engineer);
        ~Producer();
        float update(float delta);
        void commence();

        Composer &get_composer() const {
          return composer;
        }

        Conductor &get_conductor() const {
          return conductor;
        }

        virtual engineering::Engineer &get_engineer() const override {
          return engineer;
        }

        performing::Musical_Performer &get_performer() const {
          return *performer;
        }

        void next_section();
    };
  }
}