#pragma once

#include "commoner/dllexport.h"
#include <memory>
#include <perspective/Camera.h>

namespace lookinglass {
  class House;
}
using namespace lookinglass;

using namespace std;

namespace haft {
  class Input_Manager;

  class Input_State;

  class Input_Source;
}

namespace audio {
  class Player;

  class Speaker;
}

using namespace haft;

namespace clienting {
  class Mythic_Client : no_copy {
  private:
      unique_ptr<House> house;
      unique_ptr<Input_Manager> input_manager;
      unique_ptr<audio::Player> audio_player;
      bool _is_closing;

  public:
      Mythic_Client(House *house, audio::Speaker *speaker);

      ~Mythic_Client();

      void update();
      bool is_closing();

      House &get_house() const {
        return *house;
      }

      Input_Manager &get_input_manager() const {
        return *input_manager.get();
      }

      Input_State &get_current_input_state() const;

      void close() {
        _is_closing = true;
      }

      void release();
      void load();

      audio::Player &get_audio_player() const {
        return *audio_player;
      }
  };
}