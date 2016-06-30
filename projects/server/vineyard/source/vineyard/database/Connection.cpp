#include <stdexcept>
#include "Connection.h"
#include "Database.h"
#include "Statement.h"
#include <iostream>
#include <fstream>
#include "vineyard/Ground.h"
#include <map>

#if ANDROID
#include "logger.h"
#endif

namespace vineyard {
  namespace database {

    Connection::Connection(Database *database) :
      database(*database) {
      database->increment_connections();
      if (database->static_handle) {
        is_static = true;
        handle = database->static_handle;
      }
      else {
        check(sqlite3_open(database->get_filename().c_str(), &handle), "opening database file");
      }
//      std::cout << "  this: " << (void *) this << " handle: " << (void *) handle << std::endl;
    }

    Connection::Connection(std::unique_ptr<Database> &database) : Connection(database.get()) { }

    Connection::Connection(Database &database) : Connection(&database) { }

    Connection::Connection(Ground &ground) : Connection(ground.get_database()) { }

    Connection::~Connection() {
      if (!is_static) {
//        std::cout << "- this: " << (void *) this << " handle: " << (void *) handle << std::endl;
        database.statements.clear();
        sqlite3_close(handle);
      }

      database.decrement_connections();
    }

    void Connection::log(const string &message) {
      if (Ground::is_logging()) {
#if ANDROID
        log_info("SQL| %s", message.c_str());
#elif __MINGW32__
        ofstream log_file("db.log", ios::app);
        if (log_file.is_open()) {
          log_file << message << endl;
        }
#endif
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
      database.create_static();
    }

    void Connection::release_static(Database &database) {
      database.release_static();
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
