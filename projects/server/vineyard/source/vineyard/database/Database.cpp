#include "Database.h"
#include "Connection.h"
#include "landscape/Trellis.h"

using namespace landscape;

namespace vineyard {
  namespace database {

    Database::Database(const string &filename) :
      filename(filename) {

    }

    void Database::create_table(const landscape::Trellis &trellis, Connection &connection) {
      string sql = "CREATE TABLE " + trellis.get_name() + " (\n"
                   + "id INTEGER PRIMARY KEY,\n";

      auto first = true;
      for (auto &property : trellis.get_properties()) {
        if (first) {
          first = false;
        }
        else {
          sql += ",\n";
        }
        auto info = get_type_info(property.get_type());
        sql += property.get_name() + " " + info.sql_name;
      }
      sql += "\n);";
    }
  }
}