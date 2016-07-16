#pragma once

#include <aura/sequencing/Sequencer.h>
#include <aura/music/performance/Instrument.h>
#include "dllexport.h"
#include <memory>

using namespace std;
using namespace aura::music::performance;
using namespace aura::sequencing;

namespace aura {

  class MYTHIC_EXPORT Clip : no_copy {
      shared_ptr<Instrument> instrument;
      shared_ptr<Sequencer> sequencer;
      int group_id = -1;

  public:

      Clip(const shared_ptr<Instrument> &instrument, const shared_ptr<Sequencer> &sequencer) :
        instrument(instrument), sequencer(sequencer) { }

      Instrument &get_instrument() {
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