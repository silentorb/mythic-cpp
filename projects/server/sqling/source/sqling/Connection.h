#pragma once

#include <memory>
#include <string>

struct sqlite3;

using namespace std;

namespace sqling {

  class Transaction;

  class Database;

  class Statement;

  class Connection {
//        friend class vineyard::Static_Connection;

      friend class Transaction;

      sqlite3 *handle = nullptr;
      Database &database;
      bool is_static = false;

      static void create_static(Database &database);
      static void release_static(Database &database);

  public:
      Connection(Database *database);
      Connection(Database &database);
      Connection(std::unique_ptr<Database> &database);
//      Connection(Ground &ground);
      ~Connection();

      void execute(const string &sql);
      void check(int operation_result, const string &operation_description);

      sqlite3 *get_handle() const {
        return handle;
      }

      void add_statement(const string &key, shared_ptr<Statement> &statement);
      void remove_statement(const string &key);
      shared_ptr<Statement> get_statement(const string &key);
      void log(const string &message);

      Database &get_database() const {
        return database;
      }

      long long int get_last_row_id()const ;
  };
}
