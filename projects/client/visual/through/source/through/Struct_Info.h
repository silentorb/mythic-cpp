#pragma once

#include "Field_Info.h"
#include <vector>
#include <memory>

namespace through {

  class Struct_Info {
      unsigned int id;
      string name;
      vector<Field_Info> fields;

  public:

      Struct_Info(unsigned int id, const string &name, const initializer_list<Field_Info> fields) : id(id),
                                                                                                    name(name) {
        for (auto &field: fields) {
          this->fields.push_back(field);
        }
      }

      unsigned int get_id() const {
        return id;
      }

      const string &get_name() const {
        return name;
      }

      const vector<Field_Info> &get_fields() const {
        return fields;
      }
  };
}



