#include <stdexcept>
#include "Property.h"

namespace vineyard {

  Property::Property(const string &name, Types type, const string other_trellis_name, List_Type list_type) :
    name(name), type(type), other_trellis_name(other_trellis_name), list_type(list_type) {

  }

  const Type_Info &Property::get_info() const {
    return get_type_info(get_type());
  }
}