#pragma once

#include "dllexport.h"
#include <vector>
#include <memory>

namespace landscape {
  class Trellis;
}

using namespace std;

namespace vineyard {

  namespace database {
    class Database;
  }

  class MYTHIC_EXPORT Ground {
      vector<unique_ptr<landscape::Trellis>> trellises;
      unique_ptr<database::Database> db;

      void add_trellis(landscape::Trellis *trellis);

  public:
      Ground(const string &filename, initializer_list<landscape::Trellis *> initializer);
      ~Ground();

      void initialize();

      database::Database &get_database() const {
        return *db;
      }

      void clear_database();
  };
}