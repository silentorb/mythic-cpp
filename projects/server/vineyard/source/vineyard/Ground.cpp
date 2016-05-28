#include "Ground.h"
#include "database/Database.h"
#include "landscape/Trellis.h"
#include "database/Connection.h"
#include <fstream>
#include "Seed.h"
#include "Transaction.h"
#include <vineyard/database/Query.h>

namespace vineyard {
  using namespace database;

  bool ground_logging = false;

  Ground::Ground(const string &filename, initializer_list<landscape::Trellis *> initializer) :
    db(new Database(filename)) {

    sqlite3_config(SQLITE_CONFIG_SINGLETHREAD, 1);
    clear_log();

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
    Transaction transaction(*this);
    clear_database();
    Connection connection(db);
    for (auto &trellis: trellises) {
      db->create_table(*trellis, connection);
    }
    initialized = true;
  }

  void Ground::clear_log() {
    ofstream log_file("db.log", ios::out);
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

  bool Ground::is_logging() {
    return ground_logging;
  }

  void Ground::set_logging(bool logging) {
    ground_logging = logging;
  }

}