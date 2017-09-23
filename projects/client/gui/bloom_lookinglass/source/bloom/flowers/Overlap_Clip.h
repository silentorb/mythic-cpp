#pragma once

#include "bloom/flowers/Single_Parent.h"
#include "commoner/dllexport.h"

namespace bloom {
  namespace flowers {

    class MYTHIC_EXPORT Overlap_Clip : public Single_Parent {
    public:
        virtual ~Overlap_Clip();
        virtual void render() override;
        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) override;
        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;

        virtual const string get_class_name() const override;
    };
  }
}