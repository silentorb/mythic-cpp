#pragma once

#include <vector>
#include <aura/sequencing/Beats.h>
#include <aura/performing/Tempo_Loop.h>
#include "aura/sequencing/Chord.h"
#include "Chord_Structure_Source.h"
#include <iostream>
#include <string>
#include <aura/sequencing/Chord_Structure.h>

namespace aura {
  namespace composing {
    namespace chordial {

      class Chord_Queue : public sequencing::Chord_Source {
          std::vector<sequencing::Chord_Event> events;
          performing::Tempo_Loop loop;
          Chord_Structure_Source &chord_structure_source;

          void update_duration() {
            if (events.size() > 1) {
              loop.set_beats(events[1].get_duration());
            }
          }

          void on_next_chord() {
            events.erase(events.begin());
            update_duration();
            log_chord(events[0]);
          }

          void log_chord(const sequencing::Chord_Event &chord) {
            std::cout << sequencing::get_keyname(chord.get_chord().key) << ", " << chord.get_duration() << std::endl;
          }

      public:
          Chord_Queue(Chord_Structure_Source &chord_structure_source, unsigned int sample_rate) :
            chord_structure_source(chord_structure_source), loop(sample_rate, 1) {
            loop.set_on_loop([this](sequencing::Conductor &, double, double) {
              on_next_chord();
            });
          }

          virtual const sequencing::Chord &get_chord(sequencing::Beats time = 0) override {
            float next = 0;
            int trys = 0;
            do {
              for (auto &event : events) {
                next += event.get_duration();
                if (time < next) {
                  return event.get_chord();
                }
              }

              add_chords(chord_structure_source.get_chord_structure(time));

            } while (++trys < 3);

            throw std::runtime_error("Requested chord outside of current Chord_Queue buffer range.");
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
}