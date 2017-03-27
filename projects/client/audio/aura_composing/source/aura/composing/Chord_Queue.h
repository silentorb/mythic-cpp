#pragma once

#include <vector>
#include <aura/sequencing/Beats.h>
#include <aura/performing/Tempo_Loop.h>
#include "aura/sequencing/Chord.h"
#include <iostream>
#include <string>
#include <aura/sequencing/Chord_Structure.h>

namespace aura {
  namespace composing {

    class Chord_Queue : public sequencing::Chord_Source {
        std::vector<sequencing::Chord_Event> events;
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

        void log_chord(const sequencing::Chord_Event &chord) {
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

        const std::vector<sequencing::Chord_Event> &get_chords() const {
          return events;
        }

        void add_chord(const sequencing::Chord_Event chord) {
          if (events.size() == 0)
            log_chord(chord);

          events.push_back(chord);
          update_duration();
        }

        void add_chords(const sequencing::Chord_Structure &structure) {
          for (auto &event : structure) {
            add_chord(event);
          }
        }

        void update(sequencing::Conductor &conductor) {
          if (events.size() > 1) {
            loop.update(conductor);
          }
        }

    };
  }
}