#pragma once
#include "vineyard/vineyard_export.h"

namespace vineyard {
  class Ground;

  namespace database {
    class Database;

    class Connection;
  };

  class VINEYARD_EXPORT Static_Connection {
  public:
      Static_Connection(Ground & ground);
      ~Static_Connection();
  };
}