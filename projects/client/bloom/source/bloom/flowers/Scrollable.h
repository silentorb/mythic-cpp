#pragma once

#include "Flower.h"

namespace bloom {

  class BLOOM_EXPORT Scrollable : public Flower {
      vec2 offset;

  protected:
      virtual void modify_inner() override;

  public:
      Scrollable(Flower *parent = nullptr);

      const vec2 &get_offset() const {
        return offset;
      }

      void set_offset(const vec2 &offset) {
        Scrollable::offset = offset;
      }
  };
}