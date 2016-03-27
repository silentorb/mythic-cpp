#pragma once
#include <sqlite3.h>

namespace vineyard {
  namespace database {

    class Database;

    class Connection {
        sqlite3 *handle;

    public:
        Connection(Database *database);
        ~Connection();
    };
  }
}