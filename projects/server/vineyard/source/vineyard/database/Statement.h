#pragma once

#include <sqlite3.h>
#include <string>
#include <string>

using namespace std;

namespace vineyard {
  namespace database {
    class Connection;

    class Statement {
        sqlite3_stmt *handle;
        Connection &connection;
        const string name;
        const string debug_sql;

    public:
        Statement(const string &sql, Connection &connection, const string name = "");

        ~Statement();

        bool step();
        void bind(const string &key, const string &value);
        void unbind();

        sqlite3_stmt *get_handle() const {
          return handle;
        }
    };
  }
}