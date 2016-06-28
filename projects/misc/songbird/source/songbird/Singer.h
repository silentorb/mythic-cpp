#pragma once

#include "dllexport.h"
#include "Song.h"
#include <functional>
#include <vector>
#include "Listener_Channel.h"
#include <memory>
#include "promising/Promise.h"

using namespace std;

typedef function<void()> Empty_Delegate;

namespace songbird {

  class MYTHIC_EXPORT Singer {
      vector<unique_ptr<Channel_Interface>> channels;
      shared_ptr<bool> _is_deleted;

  protected:
      // Being a shared variable allows this variable to persist in local variables
      //  after the Singer is deleted.

//      void set_singer_deleted() {
//        *_is_deleted = true;
//      }

      const shared_ptr<bool> &get_is_deleted() const {
        return _is_deleted;
      }

  protected:
      Singer(Singer const &) = delete;
      Singer &operator=(Singer const &) = delete;

  public:
      Singer() : _is_deleted(new bool(false)) { }

      virtual ~Singer() {
        *_is_deleted = true;
      }

      template<typename T>
      Listener_Channel<T> &listen(const Song<T> &song, T dance) {
        auto channel = new Listener_Channel<T>;
        channel->id = static_cast<const void *>(&song);
        channel->dance = dance;
        channels.push_back(unique_ptr<Channel_Interface>(channel));
        return *channel;
      }

      template<typename T, typename A>
      void sing(const Song<T> &song, A a) {
        shared_ptr<bool> local_is_deleted = _is_deleted;
        for (auto &channel: channels) {
          if (channel->id == static_cast<const void *>(&song)) {
            auto particular_listener = static_cast<Listener_Channel<T> *>(channel.get());
            particular_listener->dance(a);
            if (local_is_deleted)
              return;
          }
        }
      };

      template<typename R, typename A, typename T>
      promising::Promise<R> &sing(const Song<T> &song, A a) {
        shared_ptr<bool> local_is_deleted = _is_deleted;
//        return promising::Promise<R>::resolved();
        return promising::Promise<R>::unique_sequence(
          channels, function<promising::Promise<R> &(Channel_Interface *, bool &cancel)>([&, a](Channel_Interface *channel, bool &cancel) -> promising::Promise<R> & {
            if (channel->id == static_cast<const void *>(&song)) {
              auto particular_listener = static_cast<Listener_Channel<T> *>(channel);
              auto &result = particular_listener->dance(a);
              if (local_is_deleted)
                cancel = true;
//              return result;
//                throw new runtime_error("Not implemented. (Not sure how...)");

              return result;
            }
//
            return promising::Promise<R>::resolved();
          }));



//        for (auto &channel: channels) {
//          if (channel->id == static_cast<const void *>(&song)) {
//            auto particular_listener = static_cast<Listener_Channel<T> *>(channel.get());
//            particular_listener->dance(a);
//            if (local_is_deleted)
//              return;
//          }
//        }
      }

      template<typename T>
      void sing(const Song<T> &song) {
        shared_ptr<bool> local_is_deleted = _is_deleted;
        for (auto &channel: channels) {
          if (channel->id == static_cast<const void *>(&song)) {
            auto particular_listener = static_cast<Listener_Channel<T> *>(channel.get());
            particular_listener->dance();
            if (local_is_deleted)
              return;
          }
        }
      };

      template<typename T>
      bool has_listeners(const Song<T> &song) {
        for (auto &listener: channels) {
          if (listener->id == static_cast<const void *>(&song))
            return true;
        }

        return false;
      };

      void remove(Channel_Interface &channel) {
        for (int i = 0; i < channels.size(); ++i) {
          if (channels[i].get() == &channel) {
            channels.erase(channels.begin() + i);
          }
        }
      }
  };
}