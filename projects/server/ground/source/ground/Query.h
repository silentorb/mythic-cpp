#pragma once

#include <functional>
#include <vineyard/Trellis.h>
#include "seed_functions.h"
#include "Seed.h"

using namespace std;

namespace sqling {
  class Connection;
}
namespace ground {

  void query_trellis3(sqling::Connection &connection, vineyard::Trellis &trellis, const Seed_Initializer &initializer,
                     const Seed_Creator &creator);

  int query_integer(Ground &ground, const string &sql);
  Identity query_identity(Ground &ground, const string &sql);
}