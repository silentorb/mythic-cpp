#pragma once

#include "commoner/dllexport.h"
#include "Device_Frame.h"
#include "Frame_Info.h"

namespace framing {
  class MYTHIC_EXPORT Platform_Frame : public virtual Device_Frame, public virtual Frame_Info {
  protected:
      bool closing = false;

  public:
      virtual ~Platform_Frame() { }

      virtual bool is_closing() override {
        return closing;
      }

      virtual float get_pixel_scale() const override {
        return 1;
      };
  };
}