#include <vineyard/database/Connection.h>
#include "Seed.h"
#include "Ground.h"
#include "database/Update.h"

using namespace landscape;

namespace vineyard {

  Seed::Seed(Ground *ground, Trellis *trellis) :
    ground(ground), trellis(trellis) {
//    auto buffer = new char[trellis.get_block_size()];
//    data = unique_ptr<char>(buffer);

//    for (auto &property : trellis.get_properties()) {
//      initialize_field(buffer + property.get_offset(), property);
//    }
  }

  Seed::~Seed() {
//    for (auto &property : trellis.get_properties()) {
//      if (property.get_type() == Types::string) {
//        string *field = (string *) get_data() + property.get_offset();
//        delete field;
//      }
//    }

    remove();
  }

  void Seed::finalize() {
    if(!  initializing)
      throw runtime_error("Seed cannot be finalized twice.");

//#define SPACEGAME_SKIP_SAVE
#ifdef SPACEGAME_SKIP_SAVE
    return;
#endif
    initializing = false;
    save();
  }

  void Seed::initialize_field(void *pointer, const Property &property) {
//    switch (property.get_type()) {
//
//      case Types::string: {
//        auto temp = (string **) pointer;
//        *temp = new string();
//        break;
//      }
//
//      case Types::integer:
//        *(int *) pointer = 0;
//        break;
//
//      case Types::longer:
//      case Types::reference:
//        *(vineyard::Identity *) pointer = 0;
//        break;
//
////      default:
////        throw runtime_error("Not implemented.");
//    }
  }

  void Seed::load() {

  }

  void Seed::save() {
    if (!ground->is_writing_enabled())
      return;

//    update_property(ground.get_database(), trellis, property,);
    database::Connection connection(ground->get_database());
    update_seed(connection, *this);
  }

  void Seed::save_property(const landscape::Property &property, void *value) {
    if (initializing || !ground->is_writing_enabled())
      return;

    update_property(ground->get_database(), *this, property, value);
  }

  void Seed::save_property(int index) {
    if (initializing || !ground->is_writing_enabled())
      return;

    auto &property = trellis->get_property(index);
    update_property(ground->get_database(), *this, property, get_pointer(property));
  }

  void *Seed::get_pointer(const Property &property) {
    return ((char *) this) + property.get_offset();
  }

  void Seed::remove() {
    if (!ground->is_writing_enabled())
      return;

    database::Connection connection(*ground);
    remove_seed(connection, *this);
  }
}

