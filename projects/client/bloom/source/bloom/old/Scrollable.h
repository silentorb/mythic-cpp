#pragma once

#include "bloom/old/Flower_Old.h"

namespace bloom {

  class BLOOM_EXPORT Scrollable : public Flower_Old {
      vec2 offset;
      vec2 scroll_force;
      vec2 velocity;
      bool allow_user_scrolling = true;

  protected:
      virtual void modify_inner() override;

  public:
      Scrollable(Flower_Old *parent = nullptr);

      vec2 &get_offset() {
        return offset;
      }

      void set_offset(const vec2 &offset) {
        Scrollable::offset = offset;
      }

      void set_allow_user_scrolling(bool value) {
        allow_user_scrolling = value;
      }

      float get_range();
  };
}