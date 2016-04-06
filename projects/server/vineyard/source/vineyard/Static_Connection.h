#pragma once
#include "dllexport.h"

namespace vineyard {
  class Ground;

  namespace database {
    class Database;

    class Connection;
  };

  class MYTHIC_EXPORT Static_Connection {
  public:
      Static_Connection(Ground & ground);
      ~Static_Connection();
  };
}