#include "Ground.h"
#include "database/Database.h"
#include "landscape/Trellis.h"
#include "database/Connection.h"
#include <fstream>
#include "Seed.h"
#include <cstdio>

namespace vineyard {
  using namespace database;

  Ground::Ground(const string &filename, initializer_list<landscape::Trellis *> initializer) :
    db(new Database(filename)) {
    for (auto trellis : initializer) {
      add_trellis(trellis);
    }

//    if (ifstream(filename))
//      remove(filename.c_str());
    clear_database();

//    if (!ifstream(filename))
    initialize();

  }

  Ground::~Ground() { }

  void Ground::initialize() {
    Connection connection(db);
    for (auto &trellis: trellises) {
      db->create_table(*trellis, connection);
    }
  }

  void Ground::add_trellis(landscape::Trellis *trellis) {
    trellises.push_back(unique_ptr<landscape::Trellis>(trellis));
  }

  void Ground::clear_database() {
    string sql;
    for (auto &trellis: trellises) {
      sql += "DROP TABLE IF EXISTS " + trellis->get_name() + ";\n";
    }

    db->execute(sql);
  }

}