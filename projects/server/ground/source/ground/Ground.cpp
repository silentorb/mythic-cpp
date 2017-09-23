#include "Ground.h"
#include "sqling/Database.h"
#include "vineyard/Trellis.h"
#include "sqling/Connection.h"
#include <fstream>
#include "Seed.h"
#include "sqling/Transaction.h"
#include "Query.h"

namespace ground {
  using namespace sqling;

  bool ground_logging = true;

  Ground::Ground(const string &filename, initializer_list<vineyard::Trellis *> initializer, bool async) :
    db(new sqling::Database(filename, async)), _async(async) {

//    sqlite3_config(SQLITE_CONFIG_SINGLETHREAD, 1);
    clear_log();

    for (auto trellis : initializer) {
      add_trellis(trellis);
    }

    for (auto &trellis: trellises) {
      trellis->finalize(Trellis_Map([this](const string &name) -> Trellis & {
        return get_trellis(name);
      }));
    }

    if (!ifstream(filename)) {
      _file_existed = false;
      initialize();
    }
    else {
      for (auto &trellis: trellises) {
        auto id = query_identity(*this, "SELECT id FROM " + trellis->get_name() + " ORDER BY id DESC LIMIT 1;");
        trellis->set_next_id(id + 1);
      }

    }

//    db->execute("PRAGMA temp_store = memory;");
//    db->execute("PRAGMA journal_mode=WAL;");
//    db->execute("PRAGMA synchronous=1;");
  }

  Ground::~Ground() {}

  void Ground::initialize() {
    if (!_writing_enabled)
      return;

    db->wait(sqling::Wait_Flags::queue | sqling::Wait_Flags::connections, 5000);
    Transaction transaction(get_database());
    clear_database();
    sqling::Connection connection(db);
    for (auto &trellis: trellises) {
      db->create_table(*trellis, connection);
    }
    initialized = true;
  }

  void Ground::clear_log() {
#if __MINGW32__
    ofstream log_file("db.log", ios::out);
#endif
  }

  void Ground::add_trellis(vineyard::Trellis *trellis) {
    trellises.push_back(unique_ptr<vineyard::Trellis>(trellis));
  }

  void Ground::clear_database() {
//    string sql;
    for (auto &trellis: trellises) {
      db->execute("DROP TABLE IF EXISTS " + trellis->get_name() + ";");
      trellis->reset_next_id();
//      sql += "DROP TABLE IF EXISTS " + trellis->get_name() + ";\n";
    }
  }

  vineyard::Trellis &Ground::get_trellis(const string &trellis_name) const {
    for (auto &trellis: trellises) {
      if (trellis->get_name() == trellis_name)
        return *trellis;
    }

    throw runtime_error("Could not find trellis named " + trellis_name + ".");
  }

  void Ground::query_trellis(vineyard::Trellis &trellis,
                             Seed_Initializer &initializer, Seed_Creator &creator) {
    sqling::Connection connection(get_database());
    query_trellis3(connection, trellis, initializer, creator);
  }

  bool Ground::is_logging() {
    return ground_logging;
  }

  void Ground::set_logging(bool logging) {
    ground_logging = logging;
  }

  void Ground::async(sqling::Task task) {
    db->async(task);
  }

  void Ground::set_async(bool value) {
    _async = value;
    if (value)
      db->initialize_queue();
  }
}