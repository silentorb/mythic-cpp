#pragma once

#include "vineyard/vineyard_export.h"
#include "Statement.h"
#include <string>
#include <sqlite3.h>
#include <memory>
#include <map>
#include <mutex>
#include <dllexport.h>
#include "Data_Task.h"

using namespace std;

namespace landscape {
  class Trellis;

  class Property;
}

namespace vineyard {
  namespace database {

    class Connection;

    class Asynchronous_Queue;

    namespace Wait_Flags {
      enum values {
          connections = 1,
          queue = 2
      };
    };

    class VINEYARD_EXPORT Database {
        friend class vineyard::database::Connection;

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

        void create_table(const landscape::Trellis &trellis, Connection &connection);
        void execute(const string &sql);

        mutex &get_mutex() {
          return m;
        }

        void async(database::Data_Task task);
        void create_static();
        void release_static();
        void wait(int conditions, int millisecond_timeout = 1000);

    };
  }
}