#include "Transaction.h"
#include "database/Connection.h"
#include "Ground.h"

namespace vineyard {
  using namespace database;

  Transaction::Transaction(Ground &ground) :
    ground(ground) {

    Connection::create_static(ground.get_database());

#ifndef ANDROID
    {
      Connection connection(ground);
      connection.execute("BEGIN TRANSACTION;");
    }
#endif
  }

  Transaction::~Transaction() {
#ifndef ANDROID
    {
      Connection connection(ground);
      connection.execute("END TRANSACTION;");
    }
#endif

    Connection::release_static(ground.get_database());
  }
}