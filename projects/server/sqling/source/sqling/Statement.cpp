#include "Statement.h"
#include "Connection.h"
#include <thread>
#include <sqlite3.h>

namespace sqling {

  Statement::Statement(const string &sql, Connection &connection, const string name) :
    connection(connection), name(name), debug_sql(sql) {
    int step = 0;
    while (true) {
      auto operation_result = sqlite3_prepare_v2(connection.get_handle(), sql.c_str(), sql.size(), &handle, nullptr);
      if (operation_result != SQLITE_OK) {
        if (operation_result == SQLITE_BUSY && step++ < 10) {
          this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        else {
          auto message =
            "Error creating statement: " + to_string(operation_result) + " " + sqlite3_errmsg(connection.get_handle());
//                  log(message);
          throw runtime_error(message);
        }
      }
      else {
        break;
      }

    }

  }

  Statement::~Statement() {
    connection.check(sqlite3_finalize(handle),
                     "closing statement");
  }

  bool Statement::step() {
    int i = 0;
    while (true) {
      int result = sqlite3_step(handle);
      connection.log(debug_sql);

      if (result == SQLITE_DONE)
        return 0;

      if (result == SQLITE_ROW)
        return 1;

      if (result == SQLITE_BUSY) {
        if (i++ > 1000)
          throw runtime_error("Timeout waiting to lock database.");

        continue;
      }

      auto message =
        "Error stepping through statement: " + to_string(result) + " " + sqlite3_errmsg(connection.get_handle());
      throw runtime_error(message);
    }
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

  const std::string Statement::get_string(int index) const {
    return string(reinterpret_cast<const char *>(sqlite3_column_text(handle, index)));
  }

  const int Statement::get_int(int index) const {
    return sqlite3_column_int(handle, index);
  }

  const long long int Statement::get_int64(int index) const {
    return sqlite3_column_int64(handle, index);
  }

  const double Statement::get_double(int index) const {
    return sqlite3_column_double(handle, index);
  }

  void Statement::bind_int(int index, int value) {
    sqlite3_bind_int(handle, index, value);
  }

  void Statement::bind_string(int index, const std::string &value) {
    sqlite3_bind_text(handle, index, value.c_str(), value.size(), nullptr);
  }

  void Statement::bind_int64(int index, long long int value) {
    sqlite3_bind_int64(handle, index, value);
  }

  void Statement::bind_double(int index, double value) {
    sqlite3_bind_double(handle, index, value);
  }

  void Statement::bind_null(int index) {
    sqlite3_bind_null(handle, index);
  }

  int Statement::get_bind_parameter_index(const std::string &value) {
    return sqlite3_bind_parameter_index(handle, value.c_str());
  }

  void Statement::reset() {
    sqlite3_reset(handle);
  }
}