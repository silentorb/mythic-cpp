#pragma once

#include <string>

namespace sqling {

    class Database;

    class Helper {
        Database &database;

    public:
        Helper(Database &database);

        const std::string query_string(const std::string &sql);
        long query_long(const std::string &sql);
    };
  }