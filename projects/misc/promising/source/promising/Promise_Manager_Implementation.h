#pragma once

#include <memory>
#include <vector>
#include "Promise.h"

namespace promising {

  class Promise_Manager_Implementation : public Promise_Manager {
      std::vector<std::unique_ptr<Promise_Interface>> promises;

  public:
      virtual void add_promise(Promise_Interface &promise) override;
      void update();
      void clear();

      int get_size() {
        return promises.size();
      }

      static Promise_Manager_Implementation &get_global_instance();
  };
}