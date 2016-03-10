#pragma once

#include "dllexport.h"
#include <functional>
#include <memory>
#include <vector>

using namespace std;

namespace promising {

  class MYTHIC_EXPORT Promise_Interface {
      static vector<unique_ptr<Promise_Interface>> promises;

  public:
      static void add_promise(Promise_Interface &promise);
      static void update_queue();
      virtual bool update() = 0;
  };

  template<typename T>
  class MYTHIC_EXPORT Promise : public Promise_Interface {

      function<T()> action;
      vector<Promise*> side_effects;
      bool _is_done;

      Promise() : action([]() { }) { }

      Promise(function<T()> action) : action(action) {
      }

  public:

      void resolve() {
        _is_done = true;
      }

      Promise &then(function<T()> action) {
        auto& promise = create(action);
        side_effects.push_back(&promise);
        return promise;
      }

      static Promise &create() {
        auto promise = new Promise<T>();
        Promise_Interface::add_promise(*promise);
        promise->_is_done = true;
        return *promise;
      }

      static Promise &create(function<T()> action) {
        auto promise = new Promise<T>(action);
        Promise_Interface::add_promise(*promise);
        return *promise;
      }

      virtual bool update() override {
        if(_is_done) {
          for (auto side_effect: side_effects) {
            side_effect->action();
          }
        }
        return _is_done;
      }
  };
}