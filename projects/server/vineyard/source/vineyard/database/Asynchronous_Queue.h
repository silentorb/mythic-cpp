#pragma once

#include "vineyard/vineyard_export.h"
#include <mutex>
#include <thread>
#include "Data_Task.h"
#include <queue>

using namespace std;

namespace vineyard {
  namespace database {

    class Database;

    typedef function<void(Database &)> Data_Task;

    class VINEYARD_EXPORT Asynchronous_Queue {
        queue<Data_Task> tasks;
        mutex m;
        Database &db;
        unique_ptr<thread> t;
				enum State {
					initializing, // No logic depends on the initializing value but it can be useful for debugging.
					active,
					closing,
					closed
				} state = State::initializing;

        void loop() {
					state = State::active;
          while (state == State::active) {
            process();
            this_thread::sleep_for(std::chrono::milliseconds(20));
          }
					state = State::closed;
				}

        void process() {
          Data_Task task;
					unique_lock<mutex>(m);
					while (tasks.size()) {
            {
              task = tasks.front();
              tasks.pop();
            }
            task(db);
          }
        }

        void start() {
          if (t.get())
            throw runtime_error("Asynchronous_Queue already started.");

          t = unique_ptr<thread>(new thread{[this]() {
            loop();
          }});
          t->detach();
        }

    public:
        Asynchronous_Queue(Database &db) : db(db) {
          start();
        }

        virtual ~Asynchronous_Queue() {
					state = State::closing;

          // I tried using t->join() here but that threw an exception in MSVC.
          // My research is finding conflicting behavior on joining a detached thread
          // and I suspect that resolution may be compiler-dependent.
					while (state != State::closed) {
						this_thread::sleep_for(std::chrono::milliseconds(10));
					}
        }

        void push(Data_Task &task) {
          unique_lock<mutex>(m);
					if (!task)
						throw runtime_error("Database task is empty.");

          tasks.push(task);
        }
    };
  }
}