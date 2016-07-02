#pragma once

#include <landscape/Trellis.h>
#include <mutex>
#include "vineyard/vineyard_export.h"
#include "songbird/Singer.h"
#include "Identity.h"

namespace vineyard {
  class Ground;

  class VINEYARD_EXPORT Seed {
  protected:
      Ground *ground = nullptr;
      landscape::Trellis *trellis = nullptr;
      bool initializing = true;
      shared_ptr<bool> is_deleted;
      mutex update_lock;

      // id needs to be the last field because functionality expects id to run straight into
      // whatever class the seed is embedded into.
      Identity id = 0;

      void initialize_field(void *pointer, const landscape::Property &property);

  public:
      Seed(int id);
      Seed(Ground *ground, landscape::Trellis *trellis);
      virtual ~Seed();
      void load();
      void save();
//      void save_property(const landscape::Property &property, void *value);
      void save_property(int index);

      template<typename T>
      void save(T index) {
        if (ground)
          save_property(static_cast<int>(index));
      }

      template<typename T>
      T get_value(int index) const {
        return *(T *) (this + trellis->get_property(index).get_offset());
      }

      template<typename T>
      T *get_pointer(int index) const {
        return *(T **) (this + trellis->get_property(index).get_offset());
      }

      template<typename T>
      T **get_pointer2(int index) const {
        return (T **) (this + trellis->get_property(index).get_offset());
      }

      void *get_pointer(const landscape::Property &property);
      static void *get_pointer(char *data, const landscape::Property &property);

      template<typename T>
      void set_value(int index, const T value) {
        auto pointer = get_value<T>(index);
        *pointer = value;

//        if (!initializing) {
//
//        }
      }

      template<typename T>
      void set_pointer(int index, T *value) {
        auto pointer = get_pointer2<T>(index);
        *pointer = value;

//        if (!initializing) {
//          save_property(trellis.get_property(index), pointer);
//        }
      }

      void set_value(int index, const string &value) {
        auto pointer = (string **) get_pointer2<string>(index);
        **pointer = value;

//        if (!initializing) {
//        save(trellis.get_property(index), pointer);
//        }
      }

      void finalize();

      void remove();

      const landscape::Trellis &get_trellis() const {
        return *trellis;
      }

      Identity get_id() const {
        return id;
      }

      void set_id(Identity id) {
        Seed::id = id;
      }

      char *get_data() {
        return ((char *) this) + sizeof(Seed) - sizeof(Identity);
      }

      static void set_initializing(Seed &seed) {
        seed.initializing = false;
      }
  };

  class Struct_Seed : public Seed {
  public:
      Struct_Seed() :
        Seed(nullptr, nullptr) { }

      void set_ground_and_trellis(Ground *ground, landscape::Trellis *trellis) {
        this->ground = ground;
        this->trellis = trellis;
      }

  };
//  class Seed_With_Identity {
//      Seed seed;
//  public:
//      Identity id;
//  };
}