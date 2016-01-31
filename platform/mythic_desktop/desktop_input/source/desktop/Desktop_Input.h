#pragma once

#include "haft/Input_Source.h"
#include "dllexport.h"
#include "Controller_Manager.h"

using namespace haft;

namespace desktop {

  class MYTHIC_EXPORT Desktop_Input : public Input_Source {

      void update_keyboard(Input_State &state);
      void update_gamepad(Input_State &state);
      void update_mouse(Input_State &state);
      Controller_Manager gamepad_manager;

      void check_axis(double value, const Device *device, int first_trigger, Input_State &state);
      void check_negative_direction(double value, Trigger &trigger, Input_State &state);
      void check_positive_direction(double value, Trigger &trigger, Input_State &state);
      void initialize_keyboard();
      void initialize_mouse();
      void initialize_gamepad();

      Device *keyboard;
      Device *mouse;
      Device *gamepad;
  public:
      Desktop_Input(Input_Configuration &config);

      virtual Input_State *get_input_state() override;
  };
}