#pragma once

#include "Flower_Old.h"

namespace bloom {

  class BLOOM_EXPORT Scrollable : public Flower_Old {
      vec2 offset;
      vec2 scroll_force;
      vec2 velocity;

  protected:
      virtual void modify_inner() override;

  public:
      Scrollable(Flower_Old *parent = nullptr);

      const vec2 &get_offset() const {
        return offset;
      }

      void set_offset(const vec2 &offset) {
        Scrollable::offset = offset;
      }
  };
}