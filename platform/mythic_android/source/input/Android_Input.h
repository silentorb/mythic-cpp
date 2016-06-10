#pragma once

#include "haft/Input_Source.h"
#include "android_native_app_glue.h"
#include "glm/glm.hpp"

using namespace haft;
using namespace glm;

class Android_Input : public Input_Source {

//      void update_keyboard(Input_State &state);
    void update_gamepad(Input_State &state);
//      void update_mouse(Input_State &state);
//      Controller_Manager gamepad_manager;

    void check_axis(double value, const Device *device, int first_trigger, Input_State &state);
    void check_negative_direction(double value, Trigger &trigger, Input_State &state);
    void check_positive_direction(double value, Trigger &trigger, Input_State &state);
//    void initialize_keyboard();
    void initialize_mouse();
    void initialize_gamepad();
    void initialize_surface();

//      Device *keyboard;
      Device *mouse;
    Device *gamepad;
    Device *surface;

    Input_State *next_state;
    vec2 last_position;
    vec2 current_position;
    bool motion_finished;
public:
    Android_Input(Input_Configuration &config);
    void single_click(int x, int y);

    Input_State *get_input_state() override;
    void process_input(AInputEvent *event);
};
