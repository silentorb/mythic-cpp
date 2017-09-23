#pragma once

#include "Task_Eater.h"

namespace threading {

  class Background_Task {

      Task_Eater interface;

      // Exists soley to ensure the spun thread is finished before this object is deleted.
      std::mutex active_mutex;

  public:
      ~Background_Task();
      using Callback = std::function<void(Task_Eater &)>;
      void start(const Callback &action);

      // The main reason this class exists.
      void cancel();
  };
}