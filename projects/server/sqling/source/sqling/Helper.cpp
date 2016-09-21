#include "Helper.h"
#include "Connection.h"
#include "Statement.h"
#include <sqlite3.h>

using namespace std;

namespace sqling {

    Helper::Helper(Database &database) : database(database) {}

    const string Helper::query_string(const string &sql) {
      Connection connection(database);
      Statement statement(sql, connection);
      statement.step();
      return string(reinterpret_cast<const char *>(sqlite3_column_text(statement.get_handle(), 0)));
    }

    long Helper::query_long(const string &sql) {
      Connection connection(database);
      Statement statement(sql, connection);
      statement.step();
      return sqlite3_column_int(statement.get_handle(), 0);
    }

  }
