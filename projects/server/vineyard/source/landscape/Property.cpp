#include <stdexcept>
#include "Property.h"

namespace landscape {

  Property::Property(const string &name, Types type) :
    name(name), type(type) {
//    if (byte_size > 0)
//      this->byte_size = byte_size;
//    else {
//      switch (type) {
//        case Types::string:
//          this->byte_size = sizeof(void *);
//          break;
//
//        case Types::integer:
//          this->byte_size = sizeof(int);
//          break;
//
//        default:
//          throw runtime_error("Not implemented.");
//      }
//    }

  }

  const Type_Info &Property::get_info() const {
    return get_type_info(get_type());
  }
}