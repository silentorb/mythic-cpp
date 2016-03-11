#pragma once

#include "dllexport.h"
#include <functional>
#include <memory>
#include <vector>

using namespace std;

namespace promising {

  class MYTHIC_EXPORT Promise_Interface : no_copy {
      static vector<unique_ptr<Promise_Interface>> promises;

  public:
      static void add_promise(Promise_Interface &promise);
//      static void add_promise(unique_ptr<Promise_Interface> &promise);
      static void update_queue();
      virtual bool update() = 0;

      virtual ~Promise_Interface() { }
  };

  template<typename O>
  class MYTHIC_EXPORT Promise : public Promise_Interface {

      vector<unique_ptr<Promise>> dependents;
      bool _is_done = false;

      virtual void execute() {
        resolve();
      }

  protected:
      Promise() {}

  public:

      Promise(Promise &&) { }

      virtual ~Promise() override {
        int k = 0;
      }

      void resolve() {
        _is_done = true;
      }

      Promise &then(function<O()> action);

//      Promise &then(Promise &promise) {
////        dependents.push_back(unique_ptr<Promise>(promise));
//        return promise;
//      }

      static Promise &defer(function<O()> action = []() { }) {
        auto promise = new Promise(action);
        Promise_Interface::add_promise(*promise);
        return *promise;
      }

      static Promise &resolved(function<O()> action = []() { }) {
        auto &result = defer(action);
        result.resolve();
        return result;
      }

      template<typename E>
      static Promise &update_sequence(vector<E> &items, function<Promise &(E item)> action, int step) {
        return action(items[step])
          .then([&items, action, step]() -> Promise & {
            int next_step = step + 1;
            if (next_step >= items.size())
              return Promise::resolved();

            return update_sequence(items, action, next_step);
          });
      }

      template<typename E>
      static Promise &sequence(vector<E> &items, function<Promise &(E item)> action) {
        if (items.size() == 0)
          return Promise::resolved();

        int step = 0;
//        auto &promise = resolved([&items, action, step]() {
        return update_sequence(items, action, step);
//        });

//        return promise;
      }

      virtual bool update() override {
        if (_is_done) {
          for (auto &dependent: dependents) {
            dependent->execute();
            Promise_Interface::add_promise(*dependent.release());
          }
        }
        return _is_done;
      }
  };

  template<typename O>
  class Promise_Returning_Void : public Promise<O> {
      function<Promise()> action;

      Promise_Returning_Void(function<O()> action) : action(action) {
      }

      virtual void execute() override {
        auto promise = action();
        resolve();
      }

  };

  template<typename O>
  class Promise_Returning_Promise : public Promise<O> {
      function<Promise()> action;

      Promise_Returning_Promise(function<O()> action) : action(action) {
      }


      virtual void execute() override {
        auto promise = action();
        resolve();
      }
  };

  typedef Promise<void> Empty_Promise;

  template <typename O>
  Promise &Promise::then(function<O()> action) {
    auto promise = new Promise(action);
    dependents.push_back(unique_ptr<Promise>(promise));
    return *promise;
  }
}