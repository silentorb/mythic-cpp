#pragma once

#include <functional>

namespace sqling {

  class Database;

  typedef std::function<void(Database &)> Task;

}