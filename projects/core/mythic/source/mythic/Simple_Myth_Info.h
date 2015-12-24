#pragma once

#include "Myth_Info.h"

namespace mythic {

  template<typename T>
  class Simple_Myth_Info : public Myth_Info {
  private:
      string name;
  public:
      Simple_Myth_Info(string name)
        : name(name) {

      }

      virtual string get_name() {
        return name;
      }

      virtual Myth *fabricate(Mythic_Engine &engine) {
        new T(engine, name);
      }
  };
}