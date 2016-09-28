#pragma once

namespace modeling {

  class Element_Buffer {
      unsigned int id = 0;

      void initialize(int index_count, int* indices);

  public:
      const unsigned int &get_id() const {
        return id;
      }

  };
}