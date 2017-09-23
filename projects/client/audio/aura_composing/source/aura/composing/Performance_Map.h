#pragma once

#include <vector>
#include <memory>
#include <map>
#include <aura/performing/Musical_Performance.h>
#include <aura/performing/Musical_Performer.h>

namespace aura {
  namespace composing {

    template<typename Sound_Type, typename Event_Type>
    class Performance_Map {
        std::vector<std::unique_ptr<performing::Performance_Source<Sound_Type, Event_Type>>> sources;
        std::map<performing::Performance_Source<Sound_Type, Event_Type> *, performing::Musical_Performance<Sound_Type, Event_Type>*> performances;
        performing::Musical_Performer<Sound_Type, Event_Type> &performer;

    public:
        Performance_Map(performing::Musical_Performer<Sound_Type, Event_Type> &performer) :
          performer(performer) {}

        const std::vector<std::unique_ptr<performing::Performance_Source<Sound_Type, Event_Type>>> &get_sources() const {
          return sources;
        }

        void add_source(performing::Performance_Source<Sound_Type, Event_Type> *source) {
          sources.push_back(std::unique_ptr<performing::Performance_Source<Sound_Type, Event_Type>>(source));
          auto &performance = performer.add_performance(source->get_instrument(), source->get_sequencer());
          performances[source] = &performance;
        }

        void remove_source(performing::Performance_Source<Sound_Type, Event_Type> &source) {
          performer.remove(*performances[&source]);
          performances.erase(&source);
          for (int i = 0; i < sources.size(); ++i) {
            if (sources[i].get() == &source) {
              sources.erase(sources.begin() + i);
              break;
            }
          }
        }
    };
  }
}