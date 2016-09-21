#pragma once

#include <string>

struct sqlite3_stmt;

using namespace std;

namespace sqling {

  class Connection;

  class Statement {
      sqlite3_stmt *handle;
      Connection &connection;
      const string name;
      const string debug_sql;

  public:
      Statement(const string &sql, Connection &connection, const string name = "");

      ~Statement();

      bool step();
      void bind(const string &key, const string &value);
      void unbind();

      sqlite3_stmt *get_handle() const {
        return handle;
      }

      const string &get_name() const {
        return name;
      }

      const std::string get_string(int index) const;
      const int get_int(int index) const;
      const long long int get_int64(int index) const;
      const double get_double(int index) const;

      void bind_int(int index, int value);
      void bind_string(int index, const std::string &value);
      void bind_int64(int index, long long int value);
      void bind_double(int index, double value);
      void bind_null(int index);
      int get_bind_parameter_index(const std::string &value);

      void reset();
  };

}