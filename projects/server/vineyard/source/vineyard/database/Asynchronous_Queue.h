#pragma once

#include "vineyard/vineyard_export.h"
#include <mutex>
#include <thread>
#include "Data_Task.h"
#include <queue>
#include <iostream>

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
        bool running = false;

        void loop() {
          running = true;
          while (running) {
            process();
            this_thread::sleep_for(std::chrono::milliseconds(10));
          }
        }

        void process() {
          Data_Task task;
          while (tasks.size()) {
            {
              unique_lock<mutex>(m);
//              std::cout << "Running task" <<endl;
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
          running = false;
          t->join();
        }

        void push(Data_Task &task) {
          unique_lock<mutex>(m);
//          std::cout << "Pushing task" <<endl;
          tasks.push(task);
        }
    };
  }
}