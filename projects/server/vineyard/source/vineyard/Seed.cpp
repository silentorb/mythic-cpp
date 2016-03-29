#include "Seed.h"
#include "Ground.h"
#include "database/Update.h"

using namespace landscape;

namespace vineyard {

  Seed::Seed(Ground &ground, Trellis &trellis) :
    ground(ground), trellis(trellis) {
    auto buffer = new char[trellis.get_block_size()];
    data = unique_ptr<char>(buffer);

    for (auto &property : trellis.get_properties()) {
      initialize_field(buffer + property.get_offset(), property);
    }
  }

  Seed::~Seed() {
    for (auto &property : trellis.get_properties()) {
      if (property.get_type() == Types::string) {
        string *field = (string *) data.get() + property.get_offset();
        delete field;
      }
    }
  }

  void Seed::initialize_field(void *pointer, const Property &property) {
    switch (property.get_type()) {

      case Types::string: {
        auto temp = (string **) pointer;
        *temp = new string();
        break;
      }

      case Types::integer:
        *(int *) pointer = 0;
        break;

      case Types::longer:
        *(long *) pointer = 0;
        break;

//      default:
//        throw runtime_error("Not implemented.");
    }
  }

  void Seed::load() {

  }

  void Seed::save() {
//    update_property(ground.get_database(), trellis, property,);
    update_seed(ground.get_database(), *this);
  }

  void *Seed::get_pointer(const Property &property) const {
    return (data.get() + property.get_offset());
  }
}

