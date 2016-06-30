#pragma once

#include "vineyard/vineyard_export.h"
#include <sqlite3.h>
#include <memory>
#include <string>

using namespace std;

namespace vineyard {

//  class Static_Connection;

  class Transaction;

  class Ground;

  namespace database {

    class Database;

    class Statement;

    class VINEYARD_EXPORT Connection {
//        friend class vineyard::Static_Connection;

        friend class vineyard::Transaction;

        sqlite3 *handle = nullptr;
        Database &database;
        bool is_static = false;

        static void create_static(Database &database);
        static void release_static(Database &database);

    public:
        Connection(Database *database);
        Connection(Database &database);
        Connection(std::unique_ptr<Database> &database);
        Connection(Ground &ground);
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
    };
  }
}