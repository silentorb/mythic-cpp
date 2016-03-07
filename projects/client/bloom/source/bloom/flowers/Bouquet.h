#pragma once

#include "Flower.h"

namespace bloom {

  class MYTHIC_EXPORT Bouquet : public Flower {
      Flower *default_focus = nullptr;

  public:
      Bouquet(Garden &garden, shared_ptr<Style> &style, Flower *parent) : Flower(garden, style, parent) {

      }

      virtual Flower *get_default_focus() const override {
        return default_focus;
      }

      void set_default_focus(Flower *default_focus) {
        Bouquet::default_focus = default_focus;
      }
  };
}