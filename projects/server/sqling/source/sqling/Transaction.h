#pragma once

namespace sqling {
  class Database;

  class Transaction {
      Database &database;

  public:
      Transaction(Database &database);
      ~Transaction();
  };
}