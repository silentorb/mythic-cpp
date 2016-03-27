#pragma once

#include <string>

using namespace std;

namespace vineyard {
  namespace database {

    class Database {
        const string filename;

    public:
        Database(const string &filename);

        void initialize();

        const string &get_filename() const {
          return filename;
        }
    };
  }
}