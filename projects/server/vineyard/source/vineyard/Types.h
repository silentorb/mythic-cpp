#pragma once

namespace vineyard {

  enum class Types {
      integer,
      longer,
      floating,
      string,
      boolean,
      reference,
      list
  };

  struct Type_Info {
      const char * sql_name;
      int size;
  };

  Type_Info& get_type_info(Types type);
}

