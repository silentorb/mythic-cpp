#pragma once

#include <string>

using namespace std;

namespace landscape {
  class Trellis;

  class Property;
}

namespace vineyard {
  namespace database {

    class Connection;

    class Database {
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