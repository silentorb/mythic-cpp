#pragma once

#include "commoner/dllexport.h"
#include "promising_export.h"
#include <functional>
#include <memory>
#include <vector>

using namespace std;

namespace promising {

  class PROMISING_EXPORT Promise_Interface : no_copy {
      static vector<unique_ptr<Promise_Interface>> promises;

  public:
      static void add_promise(Promise_Interface &promise);
//      static void add_promise(unique_ptr<Promise_Interface> &promise);
      static void update_queue();
      static void clear();
      virtual bool update() = 0;
      static int get_size();

      virtual ~Promise_Interface() { }
  };

  template<typename O>
  class Promise : public Promise_Interface {

  protected:
      bool _is_done = false;
      vector<unique_ptr<Promise>> dependents;

      Promise() { }

      virtual void execute() {
        resolve();
      }

  public:

      Promise(Promise &&) { }

      virtual ~Promise() override { }

      void resolve() {
        _is_done = true;
      }

      Promise &void_then(function<void()> action);
      Promise &then(function<Promise<O> &()> action);
      static Promise &defer(function<O()> action = []() { });
      static Promise &resolved(function<O()> action = []() { });

      template<typename E>
      static Promise &update_sequence(vector<E> items, function<Promise &(E item, bool &)> action, int step) {
        bool cancel = false;
        return action(items[step], cancel)
          .then(static_cast<function<Promise &()>>([items, action, step, cancel]() -> Promise & {
            int next_step = step + 1;
            if (cancel || next_step >= items.size())
              return Promise::resolved();

            return update_sequence(items, action, next_step);
          }));
      }

      template<typename E>
      static Promise &sequence(vector<E> &items, function<Promise &(E item, bool &)> action) {
        if (items.size() == 0)
          return Promise::resolved();

        int step = 0;
        return update_sequence(items, action, step);
      }

      template<typename E>
      static Promise &update_reference_sequence(vector<E> &items, function<Promise &(E &item, bool &)> action, int step) {
        bool cancel = false;
        return action(items[step], cancel)
          .then(static_cast<function<Promise &()>>([&items, action, step, cancel]() -> Promise & {
            int next_step = step + 1;
            if (cancel || next_step >= items.size())
              return Promise::resolved();

            return update_reference_sequence(items, action, next_step);
          }));
      }

      template<typename E>
      static Promise &reference_sequence(vector<E> &items, function<Promise &(E &item, bool &)> action) {
        if (items.size() == 0)
          return Promise::resolved();

        int step = 0;
        return update_reference_sequence(items, action, step);
      }

      template<typename E>
      static Promise &unique_sequence(const vector<unique_ptr<E>> &items, function<Promise &(E *item, bool &)> action) {
        if (items.size() == 0)
          return Promise::resolved();

        vector<E*> clone;
        for(auto & item: items){
          clone.push_back(item.get());
        }
        int step = 0;
//        auto &promise = resolved([&items, action, step]() {
        return update_sequence(clone, action, step);
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
  class Promise_Returning_Value : public Promise<O> {
      function<O()> action;
  public:

      Promise_Returning_Value(function<O()> action) : action(action) {
      }

      virtual void execute() override {
        action();
        this->resolve();
      }
  };

  template<typename O>
  class Promise_Returning_Promise : public Promise<O> {
      function<Promise<O> &()> action;

  public:
      Promise_Returning_Promise(function<Promise<O> &()> action) : action(action) {
      }

      virtual void execute() override {
        auto &promise = action();
        promise.void_then([&]() {
          this->resolve();
        });
      }
  };

  typedef Promise<void> Empty_Promise;

  template<typename O>
  Promise<O> &Promise<O>::defer(function<O()> action) {
    auto promise = new Promise_Returning_Value<O>(action);
    Promise_Interface::add_promise(*promise);
    return *promise;
  }

  template<typename O>
  Promise<O> &Promise<O>::resolved(function<O()> action) {
    auto &result = defer(action);
    result.resolve();
    return result;
  }

  template<typename O>
  Promise<O> &Promise<O>::void_then(function<void()> action) {
    auto promise = new Promise_Returning_Value<O>(action);
    dependents.push_back(unique_ptr<Promise<O>>(promise));
    return *promise;
  }

  template<typename O>
  Promise<O> &Promise<O>::then(function<Promise<O> &()> action) {
    auto promise = new Promise_Returning_Promise<O>(action);
    dependents.push_back(unique_ptr<Promise<O>>(promise));
    return *promise;
  }
}