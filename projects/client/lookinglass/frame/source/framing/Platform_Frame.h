#pragma once

#include "dllexport.h"
#include "Device_Frame.h"
#include "Frame_Info.h"

namespace framing {
  class MYTHIC_EXPORT Platform_Frame : public Device_Frame, public Frame_Info {
  protected:
      bool closing = false;
  public:
      virtual bool is_closing() override {
        return closing;
      }

  };
}