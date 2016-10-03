#include "Seed.h"
#include "Query.h"
#include "sqling/Statement.h"
#include "sqling/Connection.h"
#include "Ground.h"

using namespace vineyard;
using namespace sqling;
#if ANDROID
#include <sstream>
template<typename T>
static std::string to_string(T value) {
  std::ostringstream os;
  os << value;
  return os.str();
}
#endif
namespace ground {

  void get_query_value(const Property &property, int i, void *value, Statement &statement) {
    switch (property.get_type()) {
      case Types::string:
        *(string *) value = statement.get_string(i);
        break;

      case Types::integer:
        *(int *) value = statement.get_int(i);
        break;

      case Types::longer:
        *(long *) value = statement.get_int(i);
        break;

      case Types::boolean:
        *(bool *) value = (bool) statement.get_int(i);
        break;

      case Types::floating:
        *(float *) value = (float) statement.get_double(i);
        break;

      case Types::reference: {

        auto id = statement.get_int(i);
        if (id == 0) {
          *(Seed **) value = nullptr;
        }
        else {
          Seed *pointer = (Seed*)property.get_other_trellis()->find_seed(id);
          if (!pointer)
            throw runtime_error("Could not find " + property.get_name() + to_string(id) + ".");

          *(Seed **) value = pointer;
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

  void query_trellis3(Connection &connection, vineyard::Trellis &trellis,
                     const Seed_Initializer &initializer, const Seed_Creator &creator) {

    auto &properties = trellis.get_properties();

    auto statement = get_query_seed_statement(trellis, connection);

    while (statement->step()) {
      auto seed = (Seed *) creator();
      Seed::set_initializing(*seed);
      for (int i = 0; i < properties.size(); ++i) {
        auto &property = properties[i];
        auto value = seed->get_pointer(property);
        get_query_value(property, i, value, *statement);
      }
      initializer(seed);
    }
  }

  int query_integer(Ground &ground, const string &sql) {
    Connection connection(ground);
    {
      Statement statement(sql, connection);
      statement.step();
      return statement.get_int(0);
    }
  }


  Identity query_identity(Ground &ground, const string &sql) {
    Connection connection(ground);
    {
      Statement statement(sql, connection);
      statement.step();
      return statement.get_int64(0);
    }
  }

}