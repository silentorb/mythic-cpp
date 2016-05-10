#pragma once

#include "vineyard/vineyard_export.h"
#include <functional>
#include <landscape/Trellis.h>
#include <vineyard/seed_functions.h>
#include "vineyard/Seed.h"

using namespace std;

namespace vineyard {
  namespace database {

    class Connection;

    VINEYARD_EXPORT void query_trellis(Connection &connection, landscape::Trellis &trellis, Seed_Initializer &initializer,
                                     Seed_Creator &creator);

    VINEYARD_EXPORT int query_integer(Ground &ground, const string &sql);
  }
}