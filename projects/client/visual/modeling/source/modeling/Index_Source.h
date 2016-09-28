#pragma once

#include <vector>

namespace modeling {

  class Index_Source {
  public:
      virtual int *get_data() = 0;
      virtual int get_count() = 0;
  };

  class Owned_Index_Source : public Index_Source {
      std::vector<int> data;

  public:
      Owned_Index_Source(unsigned int count) {
        data.reserve(count);
      }

      virtual int *get_data() override {
        return data.data();
      }

      virtual int get_count() override {
        return data.size();
      }
  };
}