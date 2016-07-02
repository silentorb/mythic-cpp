#pragma once

#include "dllexport.h"
#include "Song.h"
#include <functional>
#include <vector>
#include "Channel.h"
#include <memory>
#include "promising/Promise.h"

using namespace std;

typedef function<void()> Empty_Delegate;

namespace songbird {

  class MYTHIC_EXPORT Singer {
      vector<unique_ptr<Channel_Interface>> channels;
      shared_ptr<bool> _is_deleted;
      int channel_count = 0;

      inline int get_available_listener_index() {
        for (int i = 0; i < channels.size(); ++i) {
          if (channels[i].get() == nullptr)
            return i;
        }

        throw runtime_error("No empty slot.  Something got out of sync.");
      }

  protected:
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
      Channel<T> &listen(const Song<T> &song, T dance) {
        auto channel = new Channel<T>;
        channel->id = static_cast<const void *>(&song);
        channel->dance = dance;
        if (channel_count == channels.size()) {
          channels.push_back(unique_ptr<Channel_Interface>(channel));
        }
        else {
          int index = get_available_listener_index();
          channels[index] = unique_ptr<Channel_Interface>(channel);
        }
        ++channel_count;
        return *channel;
      }

      template<typename T, typename A>
      void sing(const Song<T> &song, A a) {
        shared_ptr<bool> local_is_deleted = _is_deleted;
        for (int i = channels.size() - 1; i >= 0; --i) {
          if (channels[i].get() == nullptr)
            continue;

          auto &channel = channels[i];
          if (channel->id == static_cast<const void *>(&song)) {
            auto particular_listener = static_cast<Channel<T> *>(channel.get());
            particular_listener->dance(a);
            if (*local_is_deleted)
              return;
          }
        }
      };

      template<typename R, typename A, typename T>
      promising::Promise<R> &sing(const Song<T> &song, A a) {
        shared_ptr<bool> local_is_deleted = _is_deleted;
        return promising::Promise<R>::unique_sequence(
          channels, function<promising::Promise<R> &(Channel_Interface *, bool &cancel)>(
            [this, local_is_deleted, &song, a](Channel_Interface *channel, bool &cancel) -> promising::Promise<R> & {
              if (has_channel(channel) && channel->id == static_cast<const void *>(&song)) {
                auto particular_listener = static_cast<Channel<T> *>(channel);
                auto &result = particular_listener->dance(a);
                if (*local_is_deleted)
                  cancel = true;

                return result;
              }
//
              return promising::Promise<R>::resolved();
            }));
      }

      template<typename R, typename A, typename B, typename T>
      promising::Promise<R> &sing(const Song<T> &song, A a, B b) {
        shared_ptr<bool> local_is_deleted = _is_deleted;
        return promising::Promise<R>::unique_sequence(
          channels, function<promising::Promise<R> &(Channel_Interface *, bool &cancel)>(
            [this, local_is_deleted, &song, a, b](Channel_Interface *channel, bool &cancel) -> promising::Promise<R> & {
              if (has_channel(channel) && channel->id == static_cast<const void *>(&song)) {
                auto particular_listener = static_cast<Channel<T> *>(channel);
                auto &result = particular_listener->dance(a, b);
                if (*local_is_deleted)
                  cancel = true;

                return result;
              }
//
              return promising::Promise<R>::resolved();
            }));
      }

      template<typename R, typename A, typename B, typename C, typename T>
      promising::Promise<R> &sing(const Song<T> &song, A a, B b, C c) {
        shared_ptr<bool> local_is_deleted = _is_deleted;
        return promising::Promise<R>::unique_sequence(
          channels, function<promising::Promise<R> &(Channel_Interface *, bool &cancel)>(
            [this, local_is_deleted, &song, a, b, c](Channel_Interface *channel, bool &cancel) -> promising::Promise<R> & {
              if (has_channel(channel) && channel->id == static_cast<const void *>(&song)) {
                auto particular_listener = static_cast<Channel<T> *>(channel);
                auto &result = particular_listener->dance(a, b, c);
                if (*local_is_deleted)
                  cancel = true;

                return result;
              }
//
              return promising::Promise<R>::resolved();
            }));
      }

      template<typename T>
      void sing(const Song<T> &song) {
        shared_ptr<bool> local_is_deleted = _is_deleted;
        for (auto &channel: channels) {
          if (channel && channel->id == static_cast<const void *>(&song)) {
            auto particular_listener = static_cast<Channel<T> *>(channel.get());
            particular_listener->dance();
            if (*local_is_deleted)
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

			bool has_channel(void *pointer) {
				if (!pointer)
					return false;

				for (auto &channel : channels) {
					if (channel.get() == pointer)
						return true;
				}

				return false;
			};

      void remove(Channel_Interface &channel) {
        for (int i = 0; i < channels.size(); ++i) {
          if (channels[i].get() == &channel) {
            channels[i].reset();
            break;
          }
        }
      }
  };
}