#pragma once

#include <memory>
#include <vector>
#include "Promise.h"
#ifdef DEBUG_PROMISES
#include <map>
#endif

namespace promising {

  class Promise_Manager_Implementation : public Promise_Manager {
      std::vector<std::unique_ptr<Promise_Interface>> promises;
#ifdef DEBUG_PROMISES
			std::map<void*, std::string> stack_traces;
#endif

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