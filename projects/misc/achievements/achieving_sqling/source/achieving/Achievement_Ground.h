#pragma once

#include <achieving/Achievement_Collection.h>

namespace sqling {
  class Database;
}

namespace achieving {

  class Achievement_Ground {
      sqling::Database &database;
      Achievement_Collection &achievements;

      void load();
      void create_table();

  public:
      Achievement_Ground(sqling::Database &database, Achievement_Collection &achievements);
  };
}