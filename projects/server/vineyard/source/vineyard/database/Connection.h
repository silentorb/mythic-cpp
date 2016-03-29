#pragma once
#include <sqlite3.h>
#include <memory>
#include <string>

using namespace std;

namespace vineyard {
  namespace database {

    class Database;

    class Connection {
        sqlite3 *handle;
        bool logging = true;

        void log(const string & message);

    public:
        Connection(Database *database);
        Connection(Database &database);
        Connection(std::unique_ptr<Database> &database);
        ~Connection();

        void execute(const string & sql);
        void check(int operation_result, const string & operation_description);

        sqlite3* get_handle()const {
          return handle;
        }

    };
  }
}