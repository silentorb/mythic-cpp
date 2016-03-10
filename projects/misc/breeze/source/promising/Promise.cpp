#include "Promise.h"

namespace promising {

  vector<unique_ptr<Promise_Interface>> Promise_Interface::promises;

  void Promise_Interface::add_promise(Promise_Interface &promise) {
    promises.push_back(unique_ptr<Promise_Interface>(&promise));
  }

  void Promise_Interface::update_queue() {
    for (int i = promises.size() - 1; i >= 0; --i) {
      if (promises[i]->update()) {
        promises.erase(promises.begin() + i);
      }
    }
  }
}