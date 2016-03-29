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
    void update_property(Database &db, Trellis &trellis, Property &property, void *value);
    void update_seed(Database &db, Seed & seed);
  }
}