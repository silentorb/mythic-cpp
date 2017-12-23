#pragma once


#include "Channel.h"
#include "Singer.h"
#include <vector>

using namespace std;

namespace songbird {

  struct Channel_Connection {
      Singer *singer;
      Channel_Interface *channel;
  };

  class Listener {
      vector<Channel_Connection> connections;

  public:
      template<typename T>
      void listen(Singer &singer, const Song<T> &song, T dance) {
        auto &channel = singer.listen(song, dance);
        channel.listener = this;
        connections.push_back({&singer, static_cast<Channel_Interface *>(&channel)});
      }

      virtual ~Listener() {
				for (int i = connections.size() - 1; i >= 0; --i) {
					connections[i].singer->remove(*connections[i].channel);
        }
      }

      void remove_connection(Channel_Interface *channel) {
        for (int i = 0; i < connections.size(); ++i) {
          if (connections[i].channel == channel) {
            connections.erase(connections.begin() + i);
            break;
          }
        }
      }
  };
}