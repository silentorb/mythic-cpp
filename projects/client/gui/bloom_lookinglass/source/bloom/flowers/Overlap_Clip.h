#pragma once

#include "bloom/flowers/Single_Parent.h"
#include "commoner/dllexport.h"

namespace bloom {
  namespace flowers {

    class MYTHIC_EXPORT Overlap_Clip : public Single_Parent {
    public:
        virtual ~Overlap_Clip();
        virtual void render() override;
    };
  }
}