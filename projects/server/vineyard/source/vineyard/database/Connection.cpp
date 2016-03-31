#include <stdexcept>
#include "Connection.h"
#include "Database.h"
#include "Statement.h"
#include <iostream>
#include <fstream>
#include "vineyard/Ground.h"

namespace vineyard {
  namespace database {

    sqlite3 *static_handle = nullptr;

    Connection::Connection(Database *database) {
      if (static_handle)
        handle = static_handle;
      else
        check(sqlite3_open(database->get_filename().c_str(), &handle), "opening database file");
    }

    Connection::Connection(std::unique_ptr<Database> &database) : Connection(database.get()) { }

    Connection::Connection(Database &database) : Connection(&database) { }
    Connection::Connection(Ground & ground) : Connection(ground.get_database()) { }

    Connection::~Connection() {
      if (handle == static_handle)
        return;

      sqlite3_close(handle);
    }

    void Connection::log(const string &message) {
      if (logging) {
        ofstream log_file("db.log", ios::app);
        if (log_file.is_open()) {
          log_file << message << endl;
        }
      }
    }

    void Connection::execute(const string &sql) {
      log(sql);
      Statement statement(sql, *this);
      statement.step();
    }

    void Connection::check(int operation_result, const string &operation_description) {
      if (operation_result != SQLITE_OK) {
        auto message =
          "Error " + operation_description + ": " + to_string(operation_result) + " " + sqlite3_errmsg(handle);
        log(message);
        throw runtime_error(message);
      }
    }
  }

  void database::Connection::create_static(Database &database) {
    if (static_handle)
      throw runtime_error("Static candle already created.");

    auto operation_result = sqlite3_open(database.get_filename().c_str(), &static_handle);
    if (operation_result != SQLITE_OK) {
      auto message =
        "Error opening database file: " + to_string(operation_result) + " " + sqlite3_errmsg(static_handle);
      throw runtime_error(message);
    }
  }

  void database::Connection::release_static() {
    if (static_handle) {
      sqlite3_close(static_handle);
      static_handle = nullptr;
    }
  }


}