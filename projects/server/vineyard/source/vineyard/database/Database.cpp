#include "Database.h"
#include "Connection.h"
#include <fstream>

namespace vineyard {
  namespace database {

    Database::Database(const string &filename) :
      filename(filename) {
      if (!ifstream(filename)) {
        initialize();
      }
    }

    void Database::initialize() {
      Connection connection(this);
    }
  }
}