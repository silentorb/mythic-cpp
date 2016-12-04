#pragma once

#include <aura/sequencing/Sequencer.h>
#include <aura/performance/Instrument_Old.h>
#include <memory>

using namespace std;
using namespace aura::sequencing;

namespace aura {

  class Clip : no_copy {
      shared_ptr<performing::Instrument_Old> instrument;
      shared_ptr<Sequencer> sequencer;
      int group_id = -1;

  public:

      Clip(const shared_ptr<performing::Instrument_Old> &instrument, const shared_ptr<Sequencer> &sequencer) :
        instrument(instrument), sequencer(sequencer) { }

        performing::Instrument_Old &get_instrument() {
        return *instrument;
      }

      Sequencer &get_sequencer() {
        return *sequencer;
      }

      int get_group_id() const {
        return group_id;
      }

      void set_group_id(int value) {
        group_id = value;
      }
  };
}