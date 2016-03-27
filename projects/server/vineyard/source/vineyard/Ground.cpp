#include "Ground.h"
#include "vineyard/database/Database.h"
#include "landscape/Trellis.h"

namespace vineyard {
  using namespace database;

  Ground::Ground(const string &filename) :
    db(new Database(filename)) {

  }

  Ground::~Ground() { }
}