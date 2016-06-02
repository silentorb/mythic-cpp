#include <vineyard/database/Connection.h>
#include <iostream>
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
    if (!initializing)
      throw runtime_error("Seed cannot be finalized twice.");

//#define SPACEGAME_SKIP_SAVE
#ifdef SPACEGAME_SKIP_SAVE
    return;
#endif
    save();
    initializing = false;
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
    if (ground->is_async()) {
      if (!initializing && !id) {
        int k = 0;
      }
//                std::cout << "Push: " << trellis->get_name() << endl;
      ground->async([this](vineyard::database::Database &db) {
        std::cout << " Run: " << trellis->get_name() << endl;
        database::Connection connection(ground->get_database());
        update_seed(connection, *this);
      });
    }
    else {
      database::Connection connection(ground->get_database());
      update_seed(connection, *this);
    }
  }

//  void Seed::save_property(const landscape::Property &property, void *value) {
//    if (initializing || !ground->is_writing_enabled())
//      return;
//
//    update_property(ground->get_database(), *this, property, value);
//  }

  void Seed::save_property(int index) {
    if (initializing || !ground->is_writing_enabled())
      return;

    auto &property = trellis->get_property(index);
    if (ground->is_async()) {
      ground->async([this, &property](vineyard::database::Database &db) {
        std::cout << " Update: " << trellis->get_name() << "." << property.get_name() << endl;
        update_property(ground->get_database(), *this, property, get_pointer(property));
      });
    }
    else {
      update_property(ground->get_database(), *this, property, get_pointer(property));
    }
  }

  void *Seed::get_pointer(const Property &property) {
    return ((char *) this) + property.get_offset();
  }

  void Seed::remove() {
    if (!ground->is_writing_enabled())
      return;

    if (ground->is_async()) {
      std::cout << " Delete: " << trellis->get_name() << endl;
      auto& trellis = get_trellis();
      auto id = get_id();
      auto local_ground = ground;
      ground->async([&trellis, id, local_ground](vineyard::database::Database &db) {
        database::Connection connection(*local_ground);
        remove_seed(connection, trellis, id);
      });
    }
    else {
      database::Connection connection(*ground);
      remove_seed(connection, *this);
    }

  }
}

