#pragma once

#include "commoner/dllexport.h"
#include <functional>
#include <memory>
#include <vector>

using namespace std;

namespace promising {

  class Promise_Manager;

  class Promise_Interface : no_copy {
  public:
      virtual bool update(Promise_Manager &manager) = 0;

      virtual ~Promise_Interface() {}
  };


  class Promise_Manager {
  public:
      virtual void add_promise(Promise_Interface &promise) = 0;
      static Promise_Manager &get_global_manager();
  };

  template<typename O>
  class Promise_With_Count;

  template<typename O>
  class Promise : public Promise_Interface {

  protected:
      bool _is_done = false;
      vector<unique_ptr<Promise>> dependents;
      Promise_Manager &manager;

      Promise(Promise_Manager &manager) : manager(manager) {}

      virtual void execute() {
        resolve();
      }

  public:
//      Promise(Promise &&) {}

      virtual ~Promise() override {}

      void resolve() {
        _is_done = true;
      }

      Promise &void_then(function<void()> action);
      Promise &then(function<Promise<O> &()> action);
      static Promise &defer(Promise_Manager &manager, function<O()> action = []() {});
      static Promise &resolved(function<O()> action = []() {});

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
      static Promise &
      update_reference_sequence(vector<E> &items, function<Promise &(E &item, bool &)> action, int step) {
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

      static Promise *all(initializer_list<Promise *> promises, Promise_Manager &manager) {
        auto result = new Promise_With_Count<O>(promises.size(), manager);
        manager.add_promise(*result);
        for (auto promise : promises) {
          promise->void_then([result]() mutable {
            result->execute();
          });
        }

        return result;
      }

      template<typename E>
      static Promise &unique_sequence(const vector<unique_ptr<E>> &items, function<Promise &(E *item, bool &)> action) {
        if (items.size() == 0)
          return Promise::resolved();

        vector<E *> clone;
        for (auto &item: items) {
          clone.push_back(item.get());
        }
        int step = 0;
//        auto &promise = resolved([&items, action, step]() {
        return update_sequence(clone, action, step);
//        });

//        return promise;
      }

      virtual bool update(Promise_Manager &manager) override {
        if (_is_done) {
          for (auto &dependent: dependents) {
            dependent->execute();
            manager.add_promise(*dependent.release());
          }
        }
        return _is_done;
      }
  };

  template<typename O>
  class Promise_Returning_Value : public Promise<O> {
      function<O()> action;
  public:

      Promise_Returning_Value(Promise_Manager &manager, function<O()> action) :
        Promise<O>(manager), action(action) {
      }

      virtual void execute() override {
        if (action)
          action();

        this->resolve();
      }
  };

  template<typename O>
  class Promise_Returning_Promise : public Promise<O> {
      function<Promise<O> &()> action;

  public:
      Promise_Returning_Promise(Promise_Manager &manager, function<Promise<O> &()> action) :
        Promise<O>(manager), action(action) {
      }

      virtual void execute() override {
        auto &promise = action();
        promise.void_then([&]() {
          this->resolve();
        });
      }
  };

  template<typename O>
  class Promise_With_Count : public Promise<O> {
      int count;

  public:
      Promise_With_Count(int count, Promise_Manager &manager) :
        count(count), Promise<O>(manager) {}

      virtual void execute() override {
        if (--count == 0)
          Promise<O>::execute();
      }
  };

  typedef Promise<void> Empty_Promise;

  template<typename O>
  Promise<O> &Promise<O>::defer(Promise_Manager &manager, function<O()> action) {
    auto promise = new Promise_Returning_Value<O>(manager, action);
    manager.add_promise(*promise);
    return *promise;
  }

  template<typename O>
  Promise<O> &Promise<O>::resolved(function<O()> action) {
    auto &result = defer(Promise_Manager::get_global_manager(), action);
    result.resolve();
    return result;
  }

  template<typename O>
  Promise<O> &Promise<O>::void_then(function<void()> action) {
    auto promise = new Promise_Returning_Value<O>(manager, action);
    dependents.push_back(unique_ptr<Promise<O>>(promise));
    return *promise;
  }

  template<typename O>
  Promise<O> &Promise<O>::then(function<Promise<O> &()> action) {
    auto promise = new Promise_Returning_Promise<O>(manager, action);
    dependents.push_back(unique_ptr<Promise<O>>(promise));
    return *promise;
  }
}