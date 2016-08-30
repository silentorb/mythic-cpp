#pragma once

#include "Field_Type.h"

namespace through {

  typedef void (*Doorway_Delegate)(int index, void *data);

  class Doorway {
      int id;
      int offset;
      Field_Type type;
      Doorway_Delegate updater;

  public:
      Doorway(int id, const Field_Type &type, int offset);

      Doorway_Delegate determine_updater(const Field_Type &type);
      void update(void *data);
  };
}


