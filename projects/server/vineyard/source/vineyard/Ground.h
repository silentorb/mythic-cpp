#pragma once

#include "dllexport.h"
#include "seed_functions.h"
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
  class Seed;

  class MYTHIC_EXPORT Ground {
      vector<unique_ptr<landscape::Trellis>> trellises;
      unique_ptr<database::Database> db;
      bool _file_existed = true;

      void add_trellis(landscape::Trellis *trellis);
//      map <landscape::Trellis*, Seedery> seedery;
      void query_trellis(landscape::Trellis &trellis, Seed_Initializer &initializer,
                                Seed_Creator &creator);

  public:
      Ground(const string &filename, initializer_list<landscape::Trellis *> initializer);
      ~Ground();

      void initialize();

      database::Database &get_database() const {
        return *db;
      }

      void clear_database();

      landscape::Trellis &get_trellis(const string &trellis_name) const;

      bool file_existed() const {
        return _file_existed;
      }

      template<typename T>
      void query_trellis(landscape::Trellis &trellis, Seed_Initializer initializer) {
        Seed_Creator creator = []() { return new T(); };
        query_trellis(trellis, initializer, creator);
      }
  };
}