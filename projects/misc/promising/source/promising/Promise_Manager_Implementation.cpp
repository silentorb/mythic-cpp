#include "Promise_Manager_Implementation.h"

using namespace std;

namespace promising {

  static unique_ptr<Promise_Manager_Implementation> global_instance;

  Promise_Manager_Implementation &Promise_Manager_Implementation::get_global_instance() {
    if (!global_instance.get()) {
      global_instance = unique_ptr<Promise_Manager_Implementation>(new Promise_Manager_Implementation());
    }

    return *global_instance;
  }

  void Promise_Manager_Implementation::add_promise(Promise_Interface &promise) {
    promises.push_back(unique_ptr<Promise_Interface>(&promise));
  }

  void Promise_Manager_Implementation::update() {
    for (int i = promises.size() - 1; i >= 0; --i) {
      if (promises[i]->update(*this)) {
        if (promises.size() == 0)
          return;

        promises.erase(promises.begin() + i);
      }
      else {
        if (promises.size() == 0)
          return;
      }
    }
  }

  void Promise_Manager_Implementation::clear() {
    promises.clear();
  }

  Promise_Manager &Promise_Manager::get_global_manager() {
    return Promise_Manager_Implementation::get_global_instance();
  }
}