#pragma once

#include <mutex>
#include <thread>
#include <queue>
#include <functional>
#include "promising_export.h"

namespace promising {

  typedef std::function<void()> Task;

  class PROMISING_EXPORT Asynchronous_Queue {
      std::queue<Task> tasks;
      std::mutex m;
      std::unique_ptr<std::thread> t;
      bool on_main_thread = true;

      enum State {
          initializing, // No logic depends on the initializing value but it can be useful for debugging.
          active,
          closing,
          closed
      } state = State::initializing;

      void loop();

  public:
      Asynchronous_Queue();
      virtual ~Asynchronous_Queue();
      void start_on_new_thread();

      void push(Task task);
      void update();

      size_t size() {
        return tasks.size();
      }
  };
}
