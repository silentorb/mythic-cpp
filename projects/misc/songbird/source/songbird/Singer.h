#pragma once

#include "dllexport.h"
#include "Song.h"
#include <functional>
#include <vector>
#include "Listener.h"
#include <memory>

using namespace std;

namespace songbird {

  class MYTHIC_EXPORT Singer {
      vector<unique_ptr<Listener_Interface>> listeners;
      shared_ptr<bool> _is_deleted;

  protected:
      // Being a shared variable allows this variable to persist in local variables
      //  after the Singer is deleted.

      void set_singer_deleted() {
        *_is_deleted = true;
      }

  public:
      Singer() : _is_deleted(new bool(false)) { }

      template<typename T>
      void listen(Song<T> &song, T dance) {
        auto listener = new Listener<T>;
        listener->id = static_cast<void *>(&song);
        listener->dance = dance;
        listeners.push_back(unique_ptr<Listener_Interface>(listener));
      }

      template<typename T, typename A>
      void sing(Song<T> &song, A a) {
        shared_ptr<bool> local_is_deleted = _is_deleted;
        for (auto &listener: listeners) {
          if (listener->id == static_cast<void *>(&song)) {
            auto particular_listener = static_cast<Listener<T> *>(listener.get());
            particular_listener->dance(a);
            if (local_is_deleted)
              return;
          }
        }
      };

      template<typename T>
      bool has_listeners(Song<T> &song) {
        for (auto &listener: listeners) {
          if (listener->id == static_cast<void *>(&song))
            return true;
        }

        return false;
      };
  };
}