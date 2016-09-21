#include "vineyard/identity.h"
#include <mutex>
#include <thread>
#include "Update.h"
#include "sqling/Connection.h"
#include "Seed.h"
#include "sqling/Statement.h"

using namespace sqling;
using namespace vineyard;

namespace ground {

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

        auto id = seed->get_id();
        if (!id) {
          throw runtime_error("Seed.id cannot be 0.");
//            int i = 0;
//            while(true) {
//              id = seed->get_id();
//              if (id)
//                break;
//
//              this_thread::sleep_for(std::chrono::milliseconds(100));
//              if (++i > 100)
//                throw runtime_error("Seed.id cannot be 0.");
//            }

        }
        return to_string(id);
      }

      default:
        throw runtime_error("Not implemented.");
    }
  }

  void bind_property(const Property &property, void *value, Statement &statement) {
    auto handle = statement.get_handle();
    auto key = property.get_name();
    auto index = statement.get_bind_parameter_index(":" + key);
    if (!index)
      throw runtime_error("Could not find SQL parameter: " + key);

    switch (property.get_type()) {
      case Types::string: {
        auto text = (string *) value;
        statement.bind_string(index, *text);
        break;
      }

      case Types::integer:
        statement.bind_int(index, *(int *) value);
        break;

      case Types::longer:
        statement.bind_int64(index, *(long *) value);
        break;

      case Types::boolean:
        statement.bind_int(index, (int) *(bool *) value);
        break;

      case Types::floating:
        statement.bind_double(index, (double) *(float *) value);
        break;

      case Types::reference: {
        auto seed = *(Seed **) value;
        if (!seed)
          statement.bind_null(index);
        else
          statement.bind_int64(index, seed->get_id());

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

  void update_property(Database &db, Identity id, const Property &property, const string &sql_value) {
    string sql = "UPDATE " + property.get_trellis().get_name()
                 + " SET " + property.get_name() + " = " + sql_value
                 + "\n WHERE id = " + to_string(id)
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
//      auto pointer = shared_ptr<Statement>(result);
//      connection.add_statement(key, pointer);
    return result;
  }

  void update_seed(Connection &connection, Seed &seed) {
    auto &trellis = seed.get_trellis();
    auto &properties = trellis.get_properties();

    auto statement = get_update_seed_statement(trellis, connection, seed.get_id() != 0);
    auto statement_deleter = unique_ptr<Statement>(statement);
    for (int i = 0; i < properties.size(); ++i) {
      if (i > 0) {
        if (properties[i].get_type() == Types::list)
          continue;
      }
      else if (seed.get_id() == 0) {
        ++i;
      }

      auto &property = properties[i];

      auto value = seed.get_pointer(property);
//        statement->bind(property.get_name(), get_sql_value(property, value));
      bind_property(property, value, *statement);
    }

    statement->step();

//      if (seed.get_id() == 0) {
//        auto id = sqlite3_last_insert_rowid(connection.get_handle());
//        Assert(id != 0);
//        seed.set_id(id);
//      }
  }

  void enumerate_values(Seed &seed, vector<string> &values) {
    auto &trellis = seed.get_trellis();
    auto &properties = trellis.get_properties();
    values.reserve(properties.size());

    for (int i = 0; i < properties.size(); ++i) {
      if (i > 0) {
        if (properties[i].get_type() == Types::list)
          continue;
      }
      else if (seed.get_id() == 0) {
        ++i;
      }

      auto &property = properties[i];
      auto value = seed.get_pointer(property);
      values.push_back(property.get_type() == Types::string
                       ? *(string *) value
                       : get_sql_value(property, value)
      );
    }
  }

  void update_seed(Connection &connection, Trellis &trellis, int seed_id, const vector<std::string> &values) {
    auto &properties = trellis.get_properties();

    auto statement = get_update_seed_statement(trellis, connection, seed_id != 0);
    auto statement_deleter = unique_ptr<Statement>(statement);
    int step = 0;
    for (int i = 0; i < properties.size(); ++i) {
      if (i > 0) {
        if (properties[i].get_type() == Types::list)
          continue;
      }
      else if (seed_id == 0) {
        ++i;
      }

      auto &property = properties[i];
      statement->bind(property.get_name(), values[step++]);
//        bind_property(property, values[step++], *statement);
    }

    statement->step();
//      if (seed_id == 0) {
//        auto id = sqlite3_last_insert_rowid(connection.get_handle());
//        Assert(id != 0);
//        return id;
//      }
//
//      return seed_id;
  }

  Identity update_seed(Connection &connection, Trellis &trellis, int id, char *data) {
    auto &properties = trellis.get_properties();

    auto statement = get_update_seed_statement(trellis, connection, id != 0);
    unique_ptr<Statement> statement_deleter(statement);
    for (int i = 0; i < properties.size(); ++i) {
      if (i > 0) {
        if (properties[i].get_type() == Types::list)
          continue;
      }
      else if (id == 0) {
        ++i;
      }

      auto &property = properties[i];

      auto value = Seed::get_pointer(data, property);
      statement->bind(property.get_name(), get_sql_value(property, value));
      bind_property(property, value, *statement);
    }

    statement->step();

    return id
           ? id
           : connection.get_last_row_id();
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

  void remove_seed(sqling::Connection &connection, Seed &seed) {
    string sql = "DELETE FROM " + seed.get_trellis().get_name()
                 + " WHERE id = " + to_string(seed.get_id()) + ";";

    connection.execute(sql);
  }

  void remove_seed(sqling::Connection &connection, const Trellis &trellis, int id) {
    string sql = "DELETE FROM " + trellis.get_name()
                 + " WHERE id = " + to_string(id) + ";";

    connection.execute(sql);
  }
}