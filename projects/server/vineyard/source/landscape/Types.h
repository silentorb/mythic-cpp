#pragma once

namespace landscape {

  enum class Types {
      integer,
      longer,
      floating,
      string,
      reference,
      list
  };

  struct Type_Info {
      const char * sql_name;
      int size;
  };

  Type_Info& get_type_info(Types type);
}

