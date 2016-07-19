#pragma once

#include <string>
#include <landscape/Property.h>
#include <landscape/Trellis.h>
#include "Database.h"

using namespace std;
using namespace landscape;

namespace vineyard {
  class Seed;

  namespace database {

    const string get_sql_value(const Property &property, void *value);
    void update_property(Database &db, Seed &seed, const Property &property, void *value);
    void update_property(Database &db, Identity id, const Property &property, const string & sql_value);
    void update_seed(Connection &connection, Seed &seed);
    void update_seed(Connection &connection, Trellis &trellis, int seed_id, const vector<string> &values);
    void enumerate_values(Seed &seed, vector<string> &values);
    Identity update_seed(Connection &connection, Trellis &trellis, int id, char *data);
    void update_lists(Connection &connection, Seed &seed);
    void update_list(Connection &connection, Seed &seed, const Property &property);
    void remove_seed(Connection &connection, Seed &seed);
    void remove_seed(Connection &connection, const Trellis &trellis, int id);
  }
}