#pragma once

#include <landscape/Trellis.h>
#include "dllexport.h"
#include "songbird/Singer.h"

namespace vineyard {
  class Ground;

  class MYTHIC_EXPORT Seed : no_copy, public songbird::Singer {
      unique_ptr<char> data;
      Ground &ground;
      landscape::Trellis &trellis;
      bool initializing = true;

      void initialize_field(void *pointer, const landscape::Property &property);

  public:
      Seed(Ground &ground, landscape::Trellis &trellis);
      ~Seed();
      virtual void load();
      virtual void save();

      template<typename T>
      T *get(int index) const {
        return (T *) (data.get() + trellis.get_property(index).get_offset());
      }

      void *get_pointer(const landscape::Property & property) const;

      template<typename T>
      void set(int index, T value) const {
        auto pointer = get<T>(index);
        *pointer = value;

        if (!initializing) {

        }
      }

      void set(int index, const string& value) const {
        auto pointer = (string**)get<string>(index);
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