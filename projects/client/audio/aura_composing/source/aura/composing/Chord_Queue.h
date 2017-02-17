#pragma once

#include <vector>
#include <aura/sequencing/Beats.h>
#include <aura/performing/Tempo_Loop.h>
#include "aura/sequencing/Chord.h"
#include <iostream>
#include <string>

namespace aura {
  namespace composing {

    class Chord_Event {
        sequencing::Chord chord;
        sequencing::Beats offset;

    public:
        Chord_Event(const sequencing::Chord &chord, sequencing::Beats offset) : chord(chord), offset(offset) {}

        const sequencing::Chord &get_chord() const {
          return chord;
        }

        sequencing::Beats get_offset() const {
          return offset;
        }
    };

    class Chord_Queue : public sequencing::Chord_Source {
        std::vector<Chord_Event> events;
        performing::Tempo_Loop loop;

        void update_duration() {
          if (events.size() > 1) {
            loop.set_beats(events[1].get_offset());
          }
        }

        void on_next_chord() {
          events.erase(events.begin());
          update_duration();
          log_chord(events[0]);
        }

        void log_chord(const Chord_Event &chord) {
          std::cout << sequencing::get_keyname(chord.get_chord().key) << ", " << chord.get_offset() << std::endl;
        }

    public:
        Chord_Queue(unsigned int sample_rate) : loop(sample_rate, 1) {
          loop.set_on_loop([this](sequencing::Conductor &, double, double) {
            on_next_chord();
          });
        }

        virtual const sequencing::Chord get_chord() override {
          return events[0].get_chord();
        }

        const std::vector<Chord_Event> &get_chords() const {
          return events;
        }

        void add_chord(const Chord_Event chord) {
          if(events.size()== 0)
            log_chord(chord);

          events.push_back(chord);
          update_duration();
        }

        void update(sequencing::Conductor &conductor) {
          if (events.size() > 1) {
            loop.update(conductor);
          }
        }

    };
  }
}