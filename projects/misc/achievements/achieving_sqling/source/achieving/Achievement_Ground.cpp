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
    auto setter = [this](const Achievement &achievement, int progress) {
      Connection connection(this->database);
      Statement statement("REPLACE INTO achievement (key, progress) (:key, :progres);", connection);
      auto key_index = statement.get_bind_parameter_index(":key");
      auto progress_index = statement.get_bind_parameter_index(":progress");
      statement.bind_string(key_index, achievement.get_key());
      statement.bind_int(progress_index, progress);
      statement.step();
    };
    for (auto &achievement: achievements) {
      achievement.second->set_progress_setter(setter);
    }
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
        achievement->set_progress(progress, false);
    }
  }

  void Achievement_Ground::create_table() {
    Connection connection(database);
    connection.execute(
      "CREATE TABLE IF NOT EXISTS achievement(key UNIQUE, progress);"
    );
  }
}