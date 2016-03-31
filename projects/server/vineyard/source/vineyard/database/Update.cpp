#include <vineyard/identity.h>
#include "Update.h"
#include "Connection.h"
#include "vineyard/Seed.h"

namespace vineyard {
  namespace database {

    const string get_sql_value(const Property &property, void *value) {
      switch (property.get_type()) {
        case Types::string:
          return string("'") + *(string *) value + "'";

        case Types::integer:
          return to_string(*(int *) value);

        case Types::longer:
          return to_string(*(vineyard::Identity *) value);

        case Types::boolean:
          return to_string(*(bool *) value);

        case Types::floating:
          return to_string(*(float *) value);

        case Types::reference: {
          auto seed = *(Seed **) value;
          if (!seed)
            return "NULL";

          return to_string(seed->get_id());
        }

        default:
          throw runtime_error("Not implemented.");
      }
    }

    void update_property(Database &db, Seed &seed, const Property &property, void *value) {
      string sql = "UPDATE " + seed.get_trellis().get_name()
                   + " SET " + property.get_name() + " = " + get_sql_value(property, value)
                   + "\n WHERE id = " + to_string(seed.get_id()) + ";";

      Connection connection(db);
      connection.execute(sql);
    }

    void update_seed(Connection &connection, Seed &seed) {
      string field_names;
      string values;
      auto &trellis = seed.get_trellis();
      auto &properties = trellis.get_properties();

      for (int i = 0; i < properties.size(); ++i) {
        if (i > 0) {
          if (properties[i].get_type() == Types::list)
            continue;

          field_names += ", ";
          values += ", ";
        }
        else if (seed.get_id() == 0) {
          ++i;
        }

        auto &property = properties[i];

        field_names += property.get_name();
        auto value = seed.get_pointer(property);
        values += get_sql_value(property, value);
      }

      string sql = "REPLACE INTO " + trellis.get_name() + "(" + field_names + ")"
                   + " VALUES (" + values + ");";

//      if (seed.get_id() == 0)
//        sql += ";";
//      else
//        sql += "\n WHERE id = " + to_string(seed.get_id());

      connection.execute(sql);

      if (seed.get_id() == 0) {
        auto id = sqlite3_last_insert_rowid(connection.get_handle());
        seed.set_id(id);
      }

//      update_lists(connection, seed);
    }

    void update_lists(Connection &connection, Seed &seed) {
      for (auto &property: seed.get_trellis().get_properties()) {
        update_list(connection, seed, property);
      }
    }

    void update_list(Connection &connection, Seed &seed, const Property &property) {
      switch (property.get_list_type()) {
        case List_Type::value:

          break;

        default:
          throw runtime_error("Not implemented.");
      }
    }

    void remove_seed(database::Connection &connection, Seed &seed) {
      string sql = "DELETE FROM " + seed.get_trellis().get_name()
                   + " WHERE id = " + to_string(seed.get_id()) + ";";

      connection.execute(sql);
    }
  }
}