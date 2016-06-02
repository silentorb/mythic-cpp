#pragma once
#include <functional>

namespace vineyard {
  namespace database {

    class Database;

    typedef std::function<void(Database &)> Data_Task;
  }
}