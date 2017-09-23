#include <sqling/Statement.h>
#include "Achievement_Ground.h"
#include "sqling/Database.h"
#include "sqling/Connection.h"
#include <achieving/Achievement.h>

using namespace sqling;
using namespace vineyard;

namespace achieving {

  Achievement_Ground::Achievement_Ground(sqling::Database &database, Achievement_Collection &achievements) :
    database(database), achievements(achievements) {
    create_table();
    load();
  }

  void Achievement_Ground::load() {
    Connection connection(database);
    Statement statement("SELECT key, progress FROM achievement;", connection);

    while (statement.step()) {
      auto key = statement.get_string(0);
      auto &achievement = achievements[key];
      auto progress = statement.get_int(1);
      if (progress > achievement->get_progress())
        achievement->set_progress(progress);
    }
  }

  void Achievement_Ground::create_table() {
    Connection connection(database);
    connection.execute(
      "CREATE TABLE IF NOT EXISTS achievement(key UNIQUE, progress);"
    );
  }

  void Achievement_Ground::save_achievement(const Achievement &achievement) {
    Connection connection(database);
    Statement statement("REPLACE INTO achievement (key, progress) VALUES (:key, :progress);", connection);
    auto key_index = statement.get_bind_parameter_index(":key");
    auto progress_index = statement.get_bind_parameter_index(":progress");
    statement.bind_string(key_index, achievement.get_key());
    statement.bind_int(progress_index, achievement.get_progress());
    statement.step();
  }

  void Achievement_Ground::reset_achievements() {
    Connection connection(database);
    connection.execute("DELETE FROM achievement;");
    for (auto &achievement: achievements) {
      achievement.second->set_progress(0);
    }
  }
}