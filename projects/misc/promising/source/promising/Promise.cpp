#include "Promise.h"

namespace promising {

  vector<unique_ptr<Promise_Interface>> Promise_Interface::promises;

  void Promise_Interface::add_promise(Promise_Interface &promise) {
    promises.push_back(unique_ptr<Promise_Interface>(&promise));
    int k = 0;
  }

//  void Promise_Interface::add_promise(unique_ptr<Promise_Interface> &promise) {
//    promises.push_back(std::move(promise));
//  }

  void Promise_Interface::update_queue() {
    for (int i = promises.size() - 1; i >= 0; --i) {
      if (promises[i]->update()) {
        if (promises.size() == 0)
          return;

        promises.erase(promises.begin() + i);
        int k = 1;
      }
      else {
        if (promises.size() == 0)
          return;
      }
    }
  }

  void Promise_Interface::clear() {
    promises.clear();
  }
}