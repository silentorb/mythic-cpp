#include <vineyard/Seed.h>
#include "Query.h"
#include "Statement.h"
#include "Connection.h"

using namespace landscape;

namespace vineyard {
  namespace database {

    void get_query_value(const Property &property, int i, void *value, Statement *statement) {
      auto handle = statement->get_handle();
      switch (property.get_type()) {
        case Types::string:
          *(string *) value = string(reinterpret_cast<const char *>(sqlite3_column_text(handle, i)));
          break;

        case Types::integer:
          *(int *) value = sqlite3_column_int(handle, i);
          break;

        case Types::longer:
          *(long *) value = sqlite3_column_int(handle, i);
          break;

        case Types::boolean:
          *(bool *) value = sqlite3_column_int(handle, i);
          break;

        case Types::floating:
          *(float *) value = (float) sqlite3_column_double(handle, i);
          break;

        case Types::reference: {

          auto id = sqlite3_column_int(handle, i);
					if (id == 0) {
						*(Seed **)value = nullptr;
					}
					else {
						Seed* pointer = property.get_other_trellis()->find_seed(id);
						if (!pointer)
							throw runtime_error("Could not find " + property.get_name() + to_string(id) + ".");

						*(Seed **)value = pointer;
					}
          break;
        }

        default:
          throw runtime_error("Not implemented.");
      }
    }

    Statement *get_query_seed_statement(const Trellis &trellis, Connection &connection) {
      auto key = "query." + trellis.get_name();

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

        auto &property = properties[i];

        field_names += property.get_name();
        values += ":" + property.get_name();
      }

      string sql = "SELECT " + field_names
                   + "\n FROM " + trellis.get_name()
                   + "\n ORDER BY id ASC"
                   //                   + "\n WHERE id = :id"
                   + ";";

      Statement *result = new Statement(sql, connection);
      auto pointer = shared_ptr<Statement>(result);
      connection.add_statement(key, pointer);
      return result;
    }

    void query_trellis(Connection &connection, landscape::Trellis &trellis,
                       Seed_Initializer &initializer, Seed_Creator &creator) {

      auto &properties = trellis.get_properties();

      auto statement = get_query_seed_statement(trellis, connection);

      while (statement->step()) {
        auto seed = (Seed *) creator();
        Seed::set_initializing(*seed);
        for (int i = 0; i < properties.size(); ++i) {
          auto &property = properties[i];
          auto value = seed->get_pointer(property);
          get_query_value(property, i, value, statement);
        }
        initializer(seed);
      }
    }

  }
}