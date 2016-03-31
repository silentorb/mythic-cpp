#include "Transaction.h"
#include "database/Connection.h"
#include "Ground.h"

namespace vineyard {
  using namespace database;

  Transaction::Transaction(Ground &ground) :
    ground(ground) {

    Connection::create_static(ground.get_database());
    Connection connection(ground);
    connection.execute("BEGIN TRANSACTION;");
  }

  Transaction::~Transaction() {
    Connection connection(ground);
    connection.execute("END TRANSACTION;");
    Connection::release_static();
  }
}