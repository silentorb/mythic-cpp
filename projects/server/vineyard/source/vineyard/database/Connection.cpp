#include <stdexcept>
#include "Connection.h"
#include "Database.h"

namespace vineyard {
  namespace database {

    Connection::Connection(Database *database) {
      int result = sqlite3_open(database->get_filename().c_str(), &handle);
      if (result != SQLITE_OK) {
        throw runtime_error(string("SQLite Error: ") + sqlite3_errmsg(handle));
      }
    }

    Connection::Connection(std::unique_ptr<Database> &database) : Connection(database.get()) { }

    Connection::~Connection() {
      sqlite3_close(handle);
    }
  }
}