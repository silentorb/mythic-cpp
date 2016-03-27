#pragma once

#include "dllexport.h"
#include <vector>
#include <memory>

namespace landscape {
  class Trellis;
}

using namespace std;
using namespace landscape;

namespace vineyard {

  namespace database {
    class Database;
  }

  class MYTHIC_EXPORT Ground {
      vector<unique_ptr<Trellis>> trellises;
      unique_ptr<database::Database> db;

  public:
      Ground(const string &filename);
      ~Ground();
  };
}