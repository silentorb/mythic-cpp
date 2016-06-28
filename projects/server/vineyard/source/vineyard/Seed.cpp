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
    if (deleted.get())
      *deleted = true;

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

//  struct Seed_Update {
//      const Trellis *trellis;
//      Identity id;
//      vector<char *> data;
//
//      Seed_Update(Seed &seed) :
//        trellis(&seed.get_trellis()),
//        id(seed.get_id()) {
//        auto &last = trellis->get_properties().back();
//        auto byte_size = last.get_offset() + last.get_info().size - sizeof(Seed);
//        data.reserve(byte_size);
//        memcpy(data.data(), (&seed) + 1, byte_size);
//      }
//
//      void *get_pointer(const Property &property) {
//        return data[property.get_offset() - 2];
//      }
//  };

  void Seed::save() {
    if (!ground->is_writing_enabled())
      return;

    if (ground->is_async()) {
//                std::cout << "Push: " << trellis->get_name() << endl;
      if (id)
        throw runtime_error("Seed should never need to be fully saved twice.");

      if (!deleted.get())
        deleted = make_shared<bool>(false);

      auto local_deleted = deleted;

      auto local_trellis = trellis;
      ground->async([this, local_trellis, local_deleted](vineyard::database::Database &db) {
        if (*local_deleted)
          return;

        if (id)
          throw runtime_error("Seed should never need to be fully saved twice.");
//        std::cout << " Run: " << trellis->get_name() << endl;
        database::Connection connection(ground->get_database());
        update_seed(connection, *this);
      });
    }
    else {
      database::Connection connection(ground->get_database());
      update_seed(connection, *this);
    }
  }

  void Seed::save_property(int index) {
    if (initializing || !ground->is_writing_enabled())
      return;

    auto &property = trellis->get_property(index);
    if (ground->is_async()) {
        if (!deleted.get())
            deleted = make_shared<bool>(false);
        
        auto local_deleted = deleted;
        
      ground->async([this, &property, local_deleted](vineyard::database::Database &db) {
          if (*local_deleted)
              return;
          
//        std::cout << " Update: " << trellis->get_name() << "." << property.get_name() << endl;
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

  void *Seed::get_pointer(char *data, const Property &property) {
    return data + property.get_offset();
  }

  void Seed::remove() {
    if (!ground->is_writing_enabled())
      return;

    if (ground->is_async()) {
//      std::cout << " Delete: " << trellis->get_name() << endl;
      auto trellis = &get_trellis();
      auto id = get_id();
      auto local_ground = ground;
      ground->async([trellis, id, local_ground](vineyard::database::Database &db) {
        database::Connection connection(*local_ground);
        remove_seed(connection, *trellis, id);
      });
    }
    else {
      database::Connection connection(*ground);
      remove_seed(connection, *this);
    }

  }
}

