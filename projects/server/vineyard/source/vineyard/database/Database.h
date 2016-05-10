#pragma once

#include "vineyard/vineyard_export.h"
#include <string>

using namespace std;

namespace landscape {
  class Trellis;

  class Property;
}

namespace vineyard {
  namespace database {

    class Connection;

    class VINEYARD_EXPORT Database {
        const string filename;
        bool logging = true;

    public:
        Database(const string &filename);

        const string &get_filename() const {
          return filename;
        }

        void create_table(const landscape::Trellis & trellis, Connection &connection);
        void execute(const string & sql);
    };
  }
}