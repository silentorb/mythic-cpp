#include "Ground.h"
#include "database/Database.h"
#include "landscape/Trellis.h"
#include "database/Connection.h"
#include <fstream>
#include "Seed.h"
#include <vineyard/database/Query.h>

namespace vineyard {
  using namespace database;

  Ground::Ground(const string &filename, initializer_list<landscape::Trellis *> initializer) :
    db(new Database(filename)) {
    for (auto trellis : initializer) {
      add_trellis(trellis);
    }

    for (auto &trellis: trellises) {
      trellis->finalize(*this);
    }

    if (!ifstream(filename)) {
      _file_existed = false;
      initialize();
    }
  }

  Ground::~Ground() { }

  void Ground::initialize() {
    {
      ofstream log_file("db.log", ios::out);
    }
    clear_database();
    Connection connection(db);
    for (auto &trellis: trellises) {
      db->create_table(*trellis, connection);
    }
  }

  void Ground::add_trellis(landscape::Trellis *trellis) {
    trellises.push_back(unique_ptr<landscape::Trellis>(trellis));
  }

  void Ground::clear_database() {
//    string sql;
    for (auto &trellis: trellises) {
      db->execute("DROP TABLE IF EXISTS " + trellis->get_name() + ";");
//      sql += "DROP TABLE IF EXISTS " + trellis->get_name() + ";\n";
    }
  }

  landscape::Trellis &Ground::get_trellis(const string &trellis_name) const {
    for (auto &trellis: trellises) {
      if (trellis->get_name() == trellis_name)
        return *trellis;
    }

    throw runtime_error("Could not find trellis named " + trellis_name + ".");
  }


  void Ground::query_trellis(landscape::Trellis &trellis,
                           Seed_Initializer &initializer, Seed_Creator &creator) {
    database::Connection connection(*this);
    database::query_trellis(connection, trellis, initializer, creator);
  }
}