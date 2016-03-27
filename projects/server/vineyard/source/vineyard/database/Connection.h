#pragma once
#include <sqlite3.h>
#include <memory>

namespace vineyard {
  namespace database {

    class Database;

    class Connection {
        sqlite3 *handle;

    public:
        Connection(Database *database);
        Connection(std::unique_ptr<Database> &database);
        ~Connection();
    };
  }
}