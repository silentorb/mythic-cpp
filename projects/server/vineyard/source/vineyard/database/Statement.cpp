#include "Statement.h"
#include "Connection.h"

namespace vineyard {
  namespace database {

    Statement::Statement(const string &sql, Connection &connection, const string name) :
      connection(connection), name(name), debug_sql(sql) {
      connection.check(sqlite3_prepare_v2(connection.get_handle(), sql.c_str(), sql.size(), &handle, nullptr),
                       "preparing statement");
    }

    Statement::~Statement() {
      connection.check(sqlite3_finalize(handle),
                       "closing statement");
    }

    bool Statement::step() {
      int result = sqlite3_step(handle);
      connection.log(debug_sql);

      if (result == SQLITE_DONE)
        return 0;

      if (result == SQLITE_ROW)
        return 1;

      auto message ="Error stepping through statement: " + to_string(result) + " " + sqlite3_errmsg(connection.get_handle());
      throw runtime_error(message);
    }

    void Statement::unbind() {
      sqlite3_reset(handle);
    }

    void Statement::bind(const string &key, const string &value) {
      auto index = sqlite3_bind_parameter_index(handle, (":" + key).c_str());
      if (!index)
        throw runtime_error("Could not find SQL parameter: " + key);

      sqlite3_bind_text(handle, index, value.c_str(), value.size(), nullptr);
    }
  }
}