#include <iostream>
#include "Database.h"
#include "Connection.h"
#include "landscape/Trellis.h"
#include "Asynchronous_Queue.h"

using namespace landscape;

namespace vineyard {
  namespace database {

    Database::Database(const string &filename, bool async) :
      filename(filename) {
      if (async) {
        async_queue = unique_ptr<Asynchronous_Queue>(new Asynchronous_Queue(*this));
      }
    }

    Database::~Database() {
      std::cout << "Closing database." << std::endl;
      while(connection_count > 0) {
        this_thread::sleep_for(std::chrono::milliseconds(10));
      }
    }

    void Database::create_table(const landscape::Trellis &trellis, Connection &connection) {
      string sql = "CREATE TABLE " + trellis.get_name() + " (\n";
//                   + "id INTEGER PRIMARY KEY,\n";

      auto first = true;
      for (auto &property : trellis.get_properties()) {
        if (property.get_type() == Types::list)
          continue;

        if (!first)
          sql += ",\n";

        auto info = get_type_info(property.get_type());
        sql += " " + property.get_name() + " " + info.sql_name;
        if (first)
          sql += " PRIMARY KEY";

        first = false;
      }
      sql += "\n);";

      connection.execute(sql);
    }

    void Database::execute(const string &sql) {
      Connection connection(this);
      connection.execute(sql);
    }

    void Database::async(database::Data_Task task) {
      async_queue->push(task);
    }

    void Database::create_static() {
      unique_lock<mutex>(static_lock);
      if (static_handle)
        throw runtime_error("Static candle already created.");

      auto operation_result = sqlite3_open(get_filename().c_str(), &static_handle);
      std::cout << "+ " << (void *) static_handle << std::endl;
      if (operation_result != SQLITE_OK) {
        auto message =
          "Error opening database file: " + to_string(operation_result) + " " + sqlite3_errmsg(static_handle);
        throw runtime_error(message);
      }
    }

    void Database::release_static() {
      unique_lock<mutex>(static_lock);
      if (static_handle) {
        static_handle = nullptr;
        std::cout << "- " << static_handle << std::endl;
        int steps = 0;
        while(connection_count > 0) {
          this_thread::sleep_for(std::chrono::milliseconds(10));
          if (steps++ > 2000)
            throw runtime_error("Static Connection was not closed");
        }
        std::cout << "Connections closed" << std::endl;
        sqlite3_close(static_handle);
        static_handle = nullptr;
        statements.clear();
      }
    }

  }
}