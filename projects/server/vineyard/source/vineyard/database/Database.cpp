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

  }
}