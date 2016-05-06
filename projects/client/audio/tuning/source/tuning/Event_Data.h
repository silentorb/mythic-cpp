#pragma once

#include "dllexport.h"
#include "aura/sequencing/Event.h"
#include <vector>
#include <memory>

using namespace std;

using namespace aura;

namespace tuning {

  class MYTHIC_EXPORT Event_Data : no_copy {
      vector<unique_ptr<Event>> events;

  public:
      void add_event(Event *event) {
        events.push_back(unique_ptr<Event>(event));
      }

      const vector<unique_ptr<Event>> &get_events() const {
        return events;
      }
  };
}