#pragma once


#include "aura/sequencing/Event.h"
#include <vector>
#include <memory>

using namespace std;

using namespace aura;

namespace tuning {

  class Event_Data : no_copy {
      vector<unique_ptr<aura::sequencing::Event>> events;

  public:
      void add_event(aura::sequencing::Event *event) {
        events.push_back(unique_ptr<aura::sequencing::Event>(event));
      }

      const vector<unique_ptr<aura::sequencing::Event>> &get_events() const {
        return events;
      }
  };
}