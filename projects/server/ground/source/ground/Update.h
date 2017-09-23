#pragma once

#include <string>
#include <vineyard/Property.h>
#include <vineyard/Trellis.h>
#include "sqling/Database.h"

using namespace std;
using namespace vineyard;

namespace ground {
  class Seed;

  const string get_sql_value(const Property &property, void *value);
  void update_property(sqling::Database &db, Seed &seed, const Property &property, void *value);
  void update_property(sqling::Database &db, Identity id, const Property &property, const string &sql_value);
  void update_seed(sqling::Connection &connection, Seed &seed);
  void update_seed(sqling::Connection &connection, Trellis &trellis, int seed_id, const vector<string> &values);
  void enumerate_values(Seed &seed, vector<string> &values);
  Identity update_seed(sqling::Connection &connection, Trellis &trellis, int id, char *data);
  void update_lists(sqling::Connection &connection, Seed &seed);
  void update_list(sqling::Connection &connection, Seed &seed, const Property &property);
  void remove_seed(sqling::Connection &connection, Seed &seed);
  void remove_seed(sqling::Connection &connection, const Trellis &trellis, int id);
}