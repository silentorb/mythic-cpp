#include "ADSR_Envelope.h"

namespace aura {

  float ADSR_Envelope::get_value(double position) {
    switch (stage) {
      case ADSR_Stage::attack: {
        if (position < settings.attack_duration) {
          auto mod = attack_level * position / settings.attack_duration;
          if (mod > 1)
            mod = 1;

          return mod;
        }
        else {
          stage = ADSR_Stage::decay;
        }
      }

      case ADSR_Stage::decay: {
        if (position < settings.attack_duration + settings.decay_duration) {
          auto offset = position - settings.attack_duration;
          auto range = attack_level - sustain_level;
          auto mod = attack_level - range * offset / settings.decay_duration;
          if (mod < 0)
            mod = 0;
          else if (mod > 1)
            mod = 1;

          return mod;
        }
        else {
          stage = ADSR_Stage::sustain;
        }
      }

      case ADSR_Stage::sustain: {
        return sustain_level;
      }

      case ADSR_Stage::release: {
        break;
      }
    }


    return 0;
  }


}