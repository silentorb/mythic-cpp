#pragma once

#include <landscape/Trellis.h>
#include "dllexport.h"
#include "songbird/Singer.h"
#include "Identity.h"

namespace vineyard {
  class Ground;

  class MYTHIC_EXPORT Seed : no_copy, public songbird::Singer {
//      unique_ptr<char> data;
      Ground &ground;
      landscape::Trellis &trellis;
      bool initializing = true;

      void initialize_field(void *pointer, const landscape::Property &property);

  public:
      Seed(Ground &ground, landscape::Trellis &trellis);
      ~Seed();
      void load();
      void save();
      void save_property(const landscape::Property &property, void *value);
      void save_property(int index);

      template <typename T>
      void save(T index) {
        save_property(static_cast<int>(index));
      }

      template<typename T>
      T get_value(int index) const {
        return *(T *) (this + trellis.get_property(index).get_offset());
      }

      template<typename T>
      T *get_pointer(int index) const {
        return *(T **) (this + trellis.get_property(index).get_offset());
      }

      template<typename T>
      T **get_pointer2(int index) const {
        return (T **) (this + trellis.get_property(index).get_offset());
      }

      void *get_pointer(const landscape::Property &property);

      template<typename T>
      void set_value(int index, const T value) {
        auto pointer = get_value<T>(index);
        *pointer = value;

        if (!initializing) {

        }
      }

      template<typename T>
      void set_pointer(int index, T *value) {
        auto pointer = get_pointer2<T>(index);
        *pointer = value;

        if (!initializing) {
          save_property(trellis.get_property(index), pointer);
        }
      }

      void set_value(int index, const string &value) {
        auto pointer = (string **) get_pointer2<string>(index);
        **pointer = value;

        if (!initializing) {

        }
      }

      void finished_initializing() {
        initializing = false;
        save();
      }

      const landscape::Trellis &get_trellis() const {
        return trellis;
      }
  };
}