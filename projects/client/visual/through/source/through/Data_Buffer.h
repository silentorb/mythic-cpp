#pragma once

#include "commoner/dllexport.h"

namespace through {

  class MYTHIC_EXPORT Data_Buffer {
  private:
      unsigned int index;
      unsigned int id;
      int size;

  public:
      Data_Buffer() {}

      Data_Buffer(unsigned int index, unsigned int size);
      ~Data_Buffer();
      void initialize(unsigned int index, unsigned int size);
      void update(void *data);
  };
}


