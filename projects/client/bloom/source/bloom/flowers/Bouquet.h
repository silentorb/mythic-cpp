#pragma once

#include "Flower_Old.h"

namespace bloom {

  class MYTHIC_EXPORT Bouquet : public Flower_Old {
      Flower_Old *default_focus = nullptr;

  public:
      Bouquet(Garden &garden, shared_ptr<Style> &style, Flower_Old *parent) : Flower_Old(garden, style, parent) {

      }

      virtual Flower_Old *get_default_focus() const override {
        return default_focus;
      }

      void set_default_focus(Flower_Old *default_focus) {
        Bouquet::default_focus = default_focus;
      }
  };
}