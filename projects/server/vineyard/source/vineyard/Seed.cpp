#include <vineyard/database/Connection.h>
#include <iostream>
#include <thread>
#include "Seed.h"
#include "Ground.h"
#include "database/Update.h"

using namespace landscape;

namespace vineyard {

  Seed::Seed(Ground *ground, Trellis *trellis) :
    ground(ground), trellis(trellis), is_deleted(new bool(false)) {
//    auto buffer = new char[trellis.get_block_size()];
//    data = unique_ptr<char>(buffer);

//    for (auto &property : trellis.get_properties()) {
//      initialize_field(buffer + property.get_offset(), property);
//    }
  }

  Seed::Seed(int id) :
    id(id), is_deleted(new bool(false)) {

  }

  Seed::~Seed() {
    *is_deleted = true;

//    for (auto &property : trellis.get_properties()) {
//      if (property.get_type() == Types::string) {
//        string *field = (string *) get_data() + property.get_offset();
//        delete field;
//      }
//    }

    if (ground) {
      int step = 0;
      while (!id) {
#if _DEBUG
        if (step == 200) {
          throw runtime_error("Deleting unsaved seed.");
        }
#endif
        this_thread::sleep_for(std::chrono::milliseconds(10));
      }
      remove();
    }
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

  }

  void Seed::load() {

  }

  void *Seed::get_pointer(const Property &property) {
    return ((char *) this) + property.get_offset();
  }

  void *Seed::get_pointer(char *data, const Property &property) {
    return data + property.get_offset();
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

      if (*is_deleted)
        return;

      auto local_is_deleted = is_deleted;
      auto local_trellis = trellis;
      ground->async([this, local_trellis, local_is_deleted](vineyard::database::Database &db) {
//        unique_lock<mutex>(update_lock);
        if (*local_is_deleted)
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
      auto value = database::get_sql_value(property, get_pointer(property));
      auto local_id = get_id();
      auto &db = ground->get_database();
			Assert(property.get_trellis().get_name().size() > 0);
      ground->async([&db, local_id, &property, value](vineyard::database::Database &db) {
        update_property(db, local_id, property, value);
      });
    }
    else {
      update_property(ground->get_database(), *this, property, get_pointer(property));
    }
  }

  void Seed::remove() {
    if (!ground->is_writing_enabled() || !id)
      return;

    if (ground->is_async()) {
//      std::cout << " Delete: " << trellis->get_name() << endl;
      auto trellis = &get_trellis();
      auto id = get_id();
      auto local_ground = ground;
      ground->async([trellis, id, local_ground](vineyard::database::Database &db) {
        // Not sure a mutex is needed here but it might be and helps future proof
        // later code changes that could make it more needed.
        unique_lock<mutex>(update_lock);
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

