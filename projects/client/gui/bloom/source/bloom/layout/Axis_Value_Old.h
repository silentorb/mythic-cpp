#pragma once
#include "glm/vec2.hpp"

struct Axis_Value_Old {
    float near, length, absolute_far;
};

struct Axis_Values_Old {
    Axis_Value_Old x;
    Axis_Value_Old y;

};


//struct Axis_Values_Parent : public Axis_Values {
//    glm::vec2 margin = glm::vec2(0);
//};
