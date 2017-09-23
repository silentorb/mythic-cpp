#pragma once

#include <string>
#include <memory>
#include <map>
#include <mutex>
#include "Data_Task.h"
//#include <sqlite3.h>

using namespace std;
struct sqlite3;

namespace vineyard {
  class Trellis;

  class Property;
}

namespace sqling {

  class Connection;

  class Asynchronous_Queue;

  class Statement;

  namespace Wait_Flags {
    enum values {
        connections = 1,
        queue = 2
    };
  };

  class Database {
      friend class sqling::Connection;

      const string filename;
      bool logging = true;
      mutex m;
      mutex static_lock;
      unique_ptr<Asynchronous_Queue> async_queue;
      int connection_count = 0;

      void increment_connections() {
        ++connection_count;
      }

      void decrement_connections() {
        --connection_count;
      }

      sqlite3 *static_handle = nullptr;
      map<string, shared_ptr<Statement>> statements;

  public:
      Database(const string &filename, bool async = false);

      virtual ~Database();

      const string &get_filename() const {
        return filename;
      }

      void create_table(const vineyard::Trellis &trellis, Connection &connection);
      void execute(const string &sql);

      mutex &get_mutex() {
        return m;
      }

      void async(sqling::Task task);
      void create_static();
      void release_static();
      void wait(int conditions, int millisecond_timeout = 1000);
      void initialize_queue();
  };
}