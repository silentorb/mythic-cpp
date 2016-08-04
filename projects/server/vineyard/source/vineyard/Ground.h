#pragma once

#include "vineyard/vineyard_export.h"
#include "seed_functions.h"
#include <vector>
#include <memory>
#include "vineyard/database/Data_Task.h"

namespace landscape {
  class Trellis;
}

using namespace std;

namespace vineyard {

  namespace database {
    class Database;
  }

  class Seed;

  class VINEYARD_EXPORT Ground {
      vector<unique_ptr<landscape::Trellis>> trellises;
      unique_ptr<database::Database> db;
      bool _file_existed = true;

      void add_trellis(landscape::Trellis *trellis);
//      map <landscape::Trellis*, Seedery> seedery;
      void query_trellis(landscape::Trellis &trellis, Seed_Initializer &initializer,
                         Seed_Creator &creator);

      bool _writing_enabled = true;
      bool initialized = false;
      bool _async = false;

  public:
      Ground(const string &filename, initializer_list<landscape::Trellis *> initializer, bool async = false);
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

      bool is_writing_enabled() const {
        return _writing_enabled;
      }

      void set_writing_enabled(bool value) {
        this->_writing_enabled = value;
      }

      void clear_log();

      bool is_initialized() const {
        return initialized;
      }

      static bool is_logging();

      static void set_logging(bool logging);

      bool is_async() const {
        return _async;
      }

      void async(database::Task task);
      void set_async(bool value);
  };
}