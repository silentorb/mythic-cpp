#pragma once

#include "dllexport.h"

#include "Myth.h"
#include <map>
#include <memory>
#include "Myth_Info.h"
#include "Platform_Factory.h"
#include <functional>

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

  class MYTHIC_EXPORT Mythic_Engine : no_copy {
  private:
      timing::Quartz *timer;
      Client *client;
      std::map<string, unique_ptr<Myth>> myths;
      Mythic_Renderer *renderer;

  public:
      Mythic_Engine(Platform_Factory &factory, int width = 0, int height = 0);
      ~Mythic_Engine();

      template<typename T>
      T &get_myth(string name) {
//        auto key = typeid(T).hash_code();
        if (!myths.count(name)) {
          myths[name] = unique_ptr<T>(new T(*this));
        }

        return (T &) *myths[name];
      }

      void add_renderable(lookinglass::Renderable &renderable);
      void remove_renderable(lookinglass::Renderable &renderable);
      void update();
      void loop();

//      static void register_myth(Myth_Info *info);
      Client &get_client() const {
        return *client;
      }

      void add_myth(Myth *myth);
  };
}