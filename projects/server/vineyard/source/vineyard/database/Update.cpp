#include "Update.h"
#include "Connection.h"
#include "landscape/Property.h"
#include "vineyard/Seed.h"

namespace vineyard {
  namespace database {

    const string get_sql_value(const Property &property, void *value) {
      switch (property.get_type()) {
        case Types::string:
          return string("'") + **(string **) value + "'";

        case Types::integer:
            return to_string(*(int *) value);

        case Types::longer:
          return to_string(*(long *) value);

        default:
          throw runtime_error("Not implemented.");
      }
    }

    void update_property(Database &db, Trellis &trellis, Property &property, void *value) {
      string sql = "REPLACE INTO " + trellis.get_name() + "(" + property.get_name() + ")"
                   + " VALUES (" + get_sql_value(property, value) + ");";

      Connection connection(db);
      connection.execute(sql);
    }

    void update_seed(Database &db, Seed &seed) {
      string field_names;
      string values;
      auto &trellis = seed.get_trellis();
      auto &properties = trellis.get_properties();

      for (int i = 0; i < properties.size(); ++i) {
        if (i > 0) {
          field_names += ", ";
          values += ", ";
        }
        else if (*seed.get<long>(i) == 0) {
          ++i;
        }
//auto k = seed.get<long>(i);

        auto &property = properties[i];

        field_names += property.get_name();
        values += get_sql_value(property, seed.get_pointer(property));
      }

      string sql = "REPLACE INTO " + trellis.get_name() + "(" + field_names + ")"
                   + " VALUES (" + values + ");";

      Connection connection(db);
      connection.execute(sql);
    }

  }
}