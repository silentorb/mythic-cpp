#include <vineyard/identity.h>
#include "Update.h"
#include "Connection.h"
#include "vineyard/Seed.h"
#include "Statement.h"

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

    void bind_property(const Property &property, void *value, Statement &statement) {
      auto handle = statement.get_handle();
      auto key = property.get_name();
      auto index = sqlite3_bind_parameter_index(handle, (":" + key).c_str());
      if (!index)
        throw runtime_error("Could not find SQL parameter: " + key);

      switch (property.get_type()) {
        case Types::string: {
          auto text = (string *) value;
          sqlite3_bind_text(handle, index, text->c_str(), text->size(), nullptr);
          break;
        }

        case Types::integer:
          sqlite3_bind_int(handle, index, *(int *) value);
          break;

        case Types::longer:
          sqlite3_bind_int64(handle, index, *(long *) value);
          break;

        case Types::boolean:
          sqlite3_bind_int(handle, index, (int) *(bool *) value);
          break;

        case Types::floating:
          sqlite3_bind_double(handle, index, (double) *(float *) value);
          break;

        case Types::reference: {
          auto seed = *(Seed **) value;
          if (!seed)
            sqlite3_bind_null(handle, index);
          else
            sqlite3_bind_int64(handle, index, seed->get_id());

          break;
        }

        default:
          throw runtime_error("Not implemented.");
      }

    }

    void update_property(Database &db, Seed &seed, const Property &property, void *value) {
      string sql = "UPDATE " + seed.get_trellis().get_name()
                   + " SET " + property.get_name() + " = " + get_sql_value(property, value)
                   + "\n WHERE id = " + to_string(seed.get_id())
                   + ";";

      Connection connection(db);
      connection.execute(sql);
    }

    Statement *get_update_seed_statement(const Trellis &trellis, Connection &connection, bool with_id) {
      auto key = with_id
                 ? "update.id." + trellis.get_name()
                 : "update." + trellis.get_name();

      auto statement = connection.get_statement(key);
      if (statement) {
        statement->unbind();
        return statement.get();
      }

      string field_names;
      string values;
      auto &properties = trellis.get_properties();

      for (int i = 0; i < properties.size(); ++i) {
        if (i > 0) {
          if (properties[i].get_type() == Types::list)
            continue;

          field_names += ", ";
          values += ", ";
        }
        else if (!with_id) {
          ++i;
        }

        auto &property = properties[i];

        field_names += property.get_name();
        values += ":" + property.get_name();
      }

      string sql = "REPLACE INTO " + trellis.get_name() + "(" + field_names + ")"
                   + " VALUES (" + values + ");";

      Statement *result = new Statement(sql, connection);
      auto pointer = shared_ptr<Statement>(result);
      connection.add_statement(key, pointer);
      return result;
    }

    void update_seed(Connection &connection, Seed &seed) {
//      string field_names;
//      string values;
      auto &trellis = seed.get_trellis();
      auto &properties = trellis.get_properties();

      auto statement = get_update_seed_statement(trellis, connection, seed.get_id() != 0);
      for (int i = 0; i < properties.size(); ++i) {
        if (i > 0) {
          if (properties[i].get_type() == Types::list)
            continue;
//          field_names += ", ";
//          values += ", ";
        }
        else if (seed.get_id() == 0) {
          ++i;
        }

        auto &property = properties[i];

//        field_names += property.get_name();
        auto value = seed.get_pointer(property);
        statement->bind(property.get_name(), get_sql_value(property, value));
        bind_property(property, value, *statement);
      }

//      string sql = "REPLACE INTO " + trellis.get_name() + "(" + field_names + ")"
//                   + " VALUES (" + values + ");";

//      if (seed.get_id() == 0)
//        sql += ";";
//      else
//        sql += "\n WHERE id = " + to_string(seed.get_id());

//      connection.execute(sql);
      statement->step();

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