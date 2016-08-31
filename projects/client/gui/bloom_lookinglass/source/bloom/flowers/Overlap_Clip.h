#pragma once

#include "bloom/bloom_export.h"
#include "bloom/flowers/Single_Parent.h"

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Overlap_Clip : public Single_Parent {
    public:
        virtual void render() override;
    };
  }
}