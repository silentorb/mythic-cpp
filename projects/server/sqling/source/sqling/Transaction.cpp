#include "Transaction.h"
#include "Connection.h"

namespace sqling {

    Transaction::Transaction(Database & database) :
    database(database) {

    Connection::create_static(database);

#ifndef ANDROID
    {
      Connection connection(database);
      connection.execute("BEGIN TRANSACTION;");
    }
#endif
  }

  Transaction::~Transaction() {
#ifndef ANDROID
    {
      Connection connection(database);
      connection.execute("END TRANSACTION;");
    }
#endif

    Connection::release_static(database);
  }
}