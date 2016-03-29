#pragma once

#include <sqlite3.h>
#include <string>

using namespace std;

namespace vineyard {
  namespace database {
    class Connection;

    class Statement {
        sqlite3_stmt *handle;
Connection & connection;

    public:
        Statement(const string &sql, Connection &connection);
        ~Statement();

        void step();
    };
  }
}