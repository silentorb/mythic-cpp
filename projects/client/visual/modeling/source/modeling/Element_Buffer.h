#pragma once

namespace modeling {

  class Element_Buffer {
      unsigned int id = 0;

  public:
      void initialize(int index_count, unsigned short *indices);
      virtual ~Element_Buffer();

      void release();

      const unsigned int &get_id() const {
        return id;
      }

      void activate();
  };
}