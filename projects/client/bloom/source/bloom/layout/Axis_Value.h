#pragma once
#include "glm/vec2.hpp"

struct Axis_Value {
    float near, length, absolute_far;
};

struct Axis_Values {
    Axis_Value x;
    Axis_Value y;
};

//struct Axis_Values_Parent : public Axis_Values {
//    glm::vec2 margin = glm::vec2(0);
//};
