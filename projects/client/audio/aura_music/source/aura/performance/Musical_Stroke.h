#pragma once

#include <aura/engineering/Buffer.h>
#include "commoner/dllexport.h"
#include <functional>
#include <aura/sequencing/Note.h>
#include <aura/Stroke.h>

using namespace aura::sequencing;

namespace aura {
  namespace sequencing {
    class Conductor;
  }

  class MYTHIC_EXPORT Musical_Stroke : public Stroke {
      float frequency;
      Note note;

  protected:
      double progress = 0;

  public:
      Musical_Stroke(const Note &note) :
        Stroke(note.get_duration()),
        frequency(note.get_frequency()),
        note(note) {}

      virtual ~Musical_Stroke() {}

      virtual float update(float beat_delta) = 0;

      float get_frequency() const {
        return frequency;
      }

      const Note &get_note() const {
        return note;
      }
  };
}