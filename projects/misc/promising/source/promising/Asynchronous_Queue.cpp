#include "Asynchronous_Queue.h"

using namespace std;

namespace promising {
  Asynchronous_Queue::Asynchronous_Queue() {
  }

  Asynchronous_Queue::~Asynchronous_Queue() {
    state = State::closing;

    // I tried using t->join() here but that threw an exception in MSVC.
    // My research is finding conflicting behavior on joining a detached thread
    // and I suspect that resolution may be compiler-dependent.
    while (state != State::closed) {
      this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }

  void Asynchronous_Queue::loop() {
    state = State::active;
    while (state == State::active) {
      update();
      this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    state = State::closed;
  }

  void Asynchronous_Queue::update() {
    Task task;
    unique_lock<mutex>(m);
    while (tasks.size()) {
      {
        task = tasks.front();
        tasks.pop();
      }
      task();
    }
  }

  void Asynchronous_Queue::start_on_new_thread() {
    if (t.get())
      throw runtime_error("Asynchronous_Queue already started.");

    t = unique_ptr<thread>(new thread{[this]() {
      loop();
    }});
    t->detach();
  }

  void Asynchronous_Queue::push(Task task) {
    unique_lock<mutex>(m);
    if (!task)
      throw runtime_error("Database task is empty.");

    tasks.push(task);
  }
}