#pragma once

#include <aura/processing/Timer.h>
#include <aura/sequencing/Beats.h>
#include <aura/sequencing/Conductor.h>

namespace aura {
  namespace performing {

    class Tempo_Timer : public processing::Time_Source {
        processing::Timer timer;
        const sequencing::Conductor &conductor;

    public:
        Tempo_Timer(const sequencing::Conductor &conductor, sequencing::Beats duration) :
          conductor(conductor), timer(duration) {}

        void operator()() {
          timer.update(conductor.get_tempo_delta());
        }

        virtual double get_duration() override {
          return timer.get_duration();
        }

        virtual double get_position() override {
          return timer.get_position();
        }

        const double &get_duration() const {
          return timer.get_duration();
        }

        const double &get_position() const {
          return timer.get_position();
        }

        bool is_finished() const {
          return timer.is_finished();
        }
    };
  }
}