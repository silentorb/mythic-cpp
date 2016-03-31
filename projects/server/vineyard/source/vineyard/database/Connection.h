#pragma once

#include <sqlite3.h>
#include <memory>
#include <string>

using namespace std;

namespace vineyard {

  class Static_Connection;
class Transaction;

  class Ground;

  namespace database {

    class Database;

    class Connection {
        friend class vineyard::Static_Connection;
        friend class vineyard::Transaction;

        sqlite3 *handle;
        bool logging = true;

        void log(const string &message);

        static void create_static(Database &database);
        static void release_static();

    public:
        Connection(Database *database);
        Connection(Database &database);
        Connection(std::unique_ptr<Database> &database);
        Connection(Ground & ground);
        ~Connection();

        void execute(const string &sql);
        void check(int operation_result, const string &operation_description);

        sqlite3 *get_handle() const {
          return handle;
        }

    };
  }
}