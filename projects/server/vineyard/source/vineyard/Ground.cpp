#include "Ground.h"
#include "vineyard/database/Database.h"
#include "landscape/Trellis.h"
#include "database/Connection.h"
#include <fstream>

namespace vineyard {
  using namespace database;

  Ground::Ground(const string &filename, initializer_list<landscape::Trellis *> initializer) :
    db(new Database(filename)) {
    for (auto trellis : initializer) {
      add_trellis(trellis);
    }

    if (!ifstream(filename)) {
      initialize();
    }
  }

  Ground::~Ground() { }

  void Ground::initialize() {
    Connection connection(db);
  }

  void Ground::add_trellis(landscape::Trellis *trellis) {
    trellises.push_back(unique_ptr<landscape::Trellis>(trellis));
  }
}