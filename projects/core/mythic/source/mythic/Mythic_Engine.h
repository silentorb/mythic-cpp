#pragma once
#include "dllexport.h"

#include "Myth.h"
#include <map>
#include <memory>
#include "Myth_Info.h"
#include <typeindex>

namespace timing {
  class MYTHIC_EXPORT Quartz;
}

namespace clienting {
  class MYTHIC_EXPORT Client;
}

namespace lookinglass {
  class MYTHIC_EXPORT Renderable;
}

using namespace clienting;
using namespace std;

namespace mythic {

  class MYTHIC_EXPORT Mythic_Renderer;

  class MYTHIC_EXPORT Mythic_Engine {
  private:
      timing::Quartz *timer;
      Client *client;
      std::map<size_t, unique_ptr<Myth>> myths;
      Mythic_Renderer *renderer;

  public:
      Mythic_Engine(Client *client);
      ~Mythic_Engine();

      template<typename T>
      T* get_myth() {
        auto key = typeid(T).hash_code();
        if (!myths.count(key)) {
          myths[key] = std::unique_ptr<Myth>((Myth *) new T(*this));
        }

        return (T *) &*myths[key];
      }

      void add_renderable(lookinglass::Renderable *renderable);
      void remove_renderable(lookinglass::Renderable *renderable);
      Client *get_client();
      void update();
      void loop();
//      static void register_myth(Myth_Info *info);
  };
}