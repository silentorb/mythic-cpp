#pragma once

#include <aura/processors/envelopes/Note_Envelope.h>
#include "dllexport.h"
#include "Note_Envelope_Generator.h"

namespace aura {
  struct MYTHIC_EXPORT ADSR {
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

  class MYTHIC_EXPORT ADSR_Envelope : public Note_Envelope {
      const ADSR &settings;
      ADSR_Stage stage = ADSR_Stage::attack;

  public:

//      ADSR_Envelope(double attack_duration, double attack_level, double decay_duration, double sustain_level,
//                    double release_duration = 0) :
//        settings(attack_duration, attack_level, decay_duration, sustain_level, release_duration) { }

      ADSR_Envelope(const ADSR &settings) : settings(settings) { }

      virtual float get_value(double position) override;
  };

  class MYTHIC_EXPORT ADSR_Envelope_Generator : public Note_Envelope_Generator {
      const ADSR settings;

  public:
      ADSR_Envelope_Generator(const ADSR &settings) : settings(settings) { }
      ADSR_Envelope_Generator(double attack_duration, double attack_level, double decay_duration, double sustain_level,
                    double release_duration = 0) :
        settings(attack_duration, attack_level, decay_duration, sustain_level, release_duration) { }

      virtual Note_Envelope *generate_envelope() override {
        return new ADSR_Envelope(settings);
      }
  };
}