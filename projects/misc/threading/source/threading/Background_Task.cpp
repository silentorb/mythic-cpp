#include "Background_Task.h"

namespace threading {

  void Task_Eater::operator()(std::initializer_list<const Simple_Task> tasks) {
    for (auto &task : tasks) {
      std::lock_guard<std::mutex> l(general_mutex);
      if (mode == Background_Task_Mode::canceled)
        return;

      task();
    }
  }

  Background_Task::~Background_Task() {
    // In case any tasks are still running
    cancel();
  }

  void Background_Task::start(const Callback &action) {
    std::lock_guard<std::mutex> l(interface.general_mutex);
    if (interface.mode != Background_Task_Mode::inactive)
      throw std::runtime_error("Async loading already in progress");

    interface.mode = Background_Task_Mode::active;
    std::thread loading_thread([this, action]() {
      std::lock_guard<std::mutex> a(active_mutex);
      action(interface);
      interface.mode = Background_Task_Mode::inactive;
    });
    loading_thread.detach();
  }

  void Background_Task::cancel() {
    {
      std::lock_guard<std::mutex> l(interface.general_mutex);
      if (interface.mode != Background_Task_Mode::active)
        return;

      interface.mode = Background_Task_Mode::canceled;
    }

    // Wait for the other thread to detect the remaining tasks were canceled and abrubtly finish itself
    std::lock_guard<std::mutex> a(active_mutex);
  }
}