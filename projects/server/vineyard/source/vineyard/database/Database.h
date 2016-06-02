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

    class VINEYARD_EXPORT Database {
        const string filename;
        bool logging = true;
        mutex m;
        unique_ptr<Asynchronous_Queue> async_queue;

    public:
        sqlite3 *static_handle = nullptr;
        map<string, shared_ptr<Statement>> statements;

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
    };
  }
}