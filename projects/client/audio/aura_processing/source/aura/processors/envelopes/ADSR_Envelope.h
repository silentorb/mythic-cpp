#pragma once

#include <aura/processors/envelopes/Note_Envelope.h>
#include <aura/processors/common_processors.h>
#include "Note_Envelope_Generator.h"

namespace aura {
  struct ADSR {
      double attack_duration;
      double attack_level;
      double decay_duration;
      double sustain_level;
      double release_duration;

      ADSR(double attack_duration, double attack_level, double decay_duration, double sustain_level = 0,
           double release_duration = 0) :
        attack_duration(attack_duration), attack_level(attack_level),
        decay_duration(decay_duration), sustain_level(sustain_level),
        release_duration(release_duration) {
      }
  };

  enum class ADSR_Stage {
      attack,
      decay,
      sustain,
      release
  };

  struct ADSR_Instance {
      float attack_level;
      float sustain_level;
      ADSR_Stage stage = ADSR_Stage::attack;

      ADSR_Instance(const ADSR &settings) {
        attack_level = convert_to_db((float)settings.attack_level);
        sustain_level = convert_to_db((float)settings.sustain_level);
      }
  };

  class ADSR_Envelope : public Note_Envelope {
      const ADSR &settings;
      ADSR_Instance instance;

  public:
      ADSR_Envelope(const ADSR &settings) : settings(settings), instance(settings) {

      }

      virtual ~ADSR_Envelope() {}

      virtual float get_value(double position) override;
  };

  class ADSR_Envelope_Generator : public Note_Envelope_Generator {
      const ADSR settings;

  public:
      ADSR_Envelope_Generator(const ADSR &settings) : settings(settings) {}

      ADSR_Envelope_Generator(double attack_duration, double attack_level, double decay_duration, double sustain_level,
                              double release_duration = 0) :
        settings(attack_duration, attack_level, decay_duration, sustain_level, release_duration) {}


      virtual ~ADSR_Envelope_Generator() {}

      virtual Note_Envelope *generate_envelope() override {
        return new ADSR_Envelope(settings);
      }
  };

 float update_ADSR(ADSR_Instance &instance, double position, const ADSR &settings);

}
