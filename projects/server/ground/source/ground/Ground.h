#pragma once

#include "seed_functions.h"
#include <vector>
#include <memory>

namespace vineyard {
  class Trellis;
}

namespace sqling {
  class Database;
  typedef std::function<void(Database &)> Task;
}

using namespace std;

namespace ground {

  class Seed;

  class Ground {
      vector<unique_ptr<vineyard::Trellis>> trellises;
      unique_ptr<sqling::Database> db;
      bool _file_existed = true;

      void add_trellis(vineyard::Trellis *trellis);
      void query_trellis(vineyard::Trellis &trellis, vineyard::Seed_Initializer &initializer,
                         vineyard::Seed_Creator &creator);

      bool _writing_enabled = true;
      bool initialized = false;
      bool _async = false;

  public:
      Ground(const string &filename, initializer_list<vineyard::Trellis *> initializer, bool async = false);
      ~Ground();

      void initialize();

      sqling::Database &get_database() const {
        return *db;
      }

      void clear_database();

      vineyard::Trellis &get_trellis(const string &trellis_name) const;

      bool file_existed() const {
        return _file_existed;
      }

      template<typename T>
      void query_trellis(vineyard::Trellis &trellis, vineyard::Seed_Initializer initializer) {
        vineyard::Seed_Creator creator = []() { return new T(); };
        query_trellis(trellis, initializer, creator);
      }

      template<typename T>
      void query_trellis2(vineyard::Trellis &trellis, vineyard::Seed_Initializer initializer) {
        vineyard::Seed_Creator creator = [this, &trellis]() { return new T(this, &trellis); };
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

      void async(sqling::Task task);
      void set_async(bool value);

      operator sqling::Database &() const { return *db; }
  };
}