#pragma once

#include <thread>
#include <mutex>

namespace threading {

  class Background_Task;

  using Simple_Task = std::function<void()>;

  enum class Background_Task_Mode {
      inactive,
      active,
      canceled,
  };

  class Task_Eater {
      friend class Background_Task;

      Background_Task_Mode mode = Background_Task_Mode::inactive;
      std::mutex general_mutex;

  public:
      // If the task sequence is canceled, the current subtask is still finished and the remaining sub tasks are cancelled.
      void operator()(std::initializer_list<const Simple_Task> tasks);
  };
}