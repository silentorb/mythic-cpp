#include <stdexcept>
#include "Connection.h"
#include "Database.h"
#include "Statement.h"
#include <iostream>
#include <fstream>
#include "vineyard/Ground.h"
#include <map>

namespace vineyard {
  namespace database {

    Connection::Connection(Database *database) :
      database(*database) {
      if (database->static_handle)
        handle = database->static_handle;
      else
        check(sqlite3_open(database->get_filename().c_str(), &handle), "opening database file");
    }

    Connection::Connection(std::unique_ptr<Database> &database) : Connection(database.get()) { }

    Connection::Connection(Database &database) : Connection(&database) { }

    Connection::Connection(Ground &ground) : Connection(ground.get_database()) { }

    Connection::~Connection() {
      if (handle == database.static_handle)
        return;

      database.statements.clear();
      sqlite3_close(handle);
    }

    void Connection::log(const string &message) {
      if (Ground::is_logging()) {
        ofstream log_file("db.log", ios::app);
        if (log_file.is_open()) {
          log_file << message << endl;
        }
      }
    }

    void Connection::execute(const string &sql) {
//      log(sql);
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

    void Connection::create_static(Database &database) {
      if (database.static_handle)
        throw runtime_error("Static candle already created.");

      auto operation_result = sqlite3_open(database.get_filename().c_str(), &database.static_handle);
      if (operation_result != SQLITE_OK) {
        auto message =
          "Error opening database file: " + to_string(operation_result) + " " + sqlite3_errmsg(database.static_handle);
        throw runtime_error(message);
      }
    }

    void Connection::release_static(Database &database) {
      if (database.static_handle) {
        sqlite3_close(database.static_handle);
        database.static_handle = nullptr;
        database.statements.clear();
      }
    }

    void Connection::add_statement(const string &key, shared_ptr<Statement> &statement) {
      database.statements[key] = statement;
    }

    void Connection::remove_statement(const string &key) {
      database.statements.erase(key);
    }

    shared_ptr<Statement> Connection::get_statement(const string &key) {
      return database.statements[key];
    }

  }
}
