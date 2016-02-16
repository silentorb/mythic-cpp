#pragma once

#include "dllexport.h"
#include "Group.h"
#include "Image_Effect.h"
#include "Draw.h"

namespace drawing {

  class MYTHIC_EXPORT Scrollable : public Group {
      Draw &draw;
      vec2 offset;

  public:

      Scrollable(Draw &draw);

      virtual void render() override;

      const vec2 &get_offset() const {
        return offset;
      }

      void set_offset(const vec2 &offset) {
        this->offset = offset;
      }
  };
}