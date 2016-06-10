#include "Transaction.h"
#include "database/Connection.h"
#include "Ground.h"

namespace vineyard {
  using namespace database;

  Transaction::Transaction(Ground &ground) :
    ground(ground) {

    Connection::create_static(ground.get_database());
    Connection connection(ground);
#ifndef ANDROID
    connection.execute("BEGIN TRANSACTION;");
#endif
  }

  Transaction::~Transaction() {
    Connection connection(ground);
#ifndef ANDROID
    connection.execute("END TRANSACTION;");
#endif
    Connection::release_static(ground.get_database());
  }
}