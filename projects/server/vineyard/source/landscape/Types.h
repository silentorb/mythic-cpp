#pragma once

namespace landscape {

  enum class Types {
      integer,
      floating,
      string,
      reference,
      list
  };

  struct Type_Info {
      const char * sql_name;
  };

  Type_Info& get_type_info(Types type);
}

