#include "Statement.h"
#include "Connection.h"

namespace vineyard {
  namespace database {

    Statement::Statement(const string &sql, Connection &connection) :
      connection(connection) {
      connection.check(sqlite3_prepare_v2(connection.get_handle(), sql.c_str(), sql.size(), &handle, nullptr),
                       "preparing statement");
    }

    Statement::~Statement() {
      connection.check(sqlite3_finalize(handle),
                       "closing statement");
    }

    void Statement::step() {
      int result = sqlite3_step(handle);
      if (result != SQLITE_DONE)
        throw runtime_error(
          string("Error opening database file: ") + to_string(result) + " " + sqlite3_errmsg(connection.get_handle()));

    }
  }
}