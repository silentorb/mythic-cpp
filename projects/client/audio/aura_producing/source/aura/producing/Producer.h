#pragma once

#include <aura/sequencing/Conductor.h>
#include <aura/performing/Performance_Producer.h>
#include "aura/performing/Tempo_Loop.h"
#include "aura/performing/Musical_Performer.h"

namespace aura {
  namespace producing {

    template<typename Sound_Type, typename Event_Type>
    class Producer : virtual public performing::Performance_Producer {
//        composing::Composer<Sound_Type, Event_Type> &composer;
        Conductor &conductor;
        engineering::Engineer &engineer;
        unique_ptr<performing::Musical_Performer<Sound_Type, Event_Type>> performer;
//        unique_ptr<performing::Tempo_Loop> chord_loop;

    public:
        Producer(Conductor &conductor, engineering::Engineer &engineer);
        ~Producer();
        float update(float delta);
        void commence();

//        composing::Composer<Sound_Type, Event_Type> &get_composer() const {
//          return composer;
//        }

        Conductor &get_conductor() const {
          return conductor;
        }

        virtual engineering::Engineer &get_engineer() const override {
          return engineer;
        }

        performing::Musical_Performer<Sound_Type, Event_Type> &get_performer() const {
          return *performer;
        }

//        void next_section();
    };
  }
}