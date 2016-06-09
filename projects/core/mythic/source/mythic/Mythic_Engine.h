#pragma once

#include "dllexport.h"

#include "Myth.h"
#include <map>
#include <memory>
#include "Myth_Info.h"
#include <functional>
#include <vector>

namespace timing {
  class MYTHIC_EXPORT Quartz;
}

namespace clienting {
  class MYTHIC_EXPORT Client;
}

namespace lookinglass {
  typedef function<void()> Renderable;
}
using namespace clienting;
using namespace std;

namespace mythic {

  class Mythic_Renderer;
  class Platform_Factory;

  class MYTHIC_EXPORT Mythic_Engine : no_copy {
  private:
      timing::Quartz *timer;
      Client *client;
      std::map<string, unique_ptr<Myth>> myths;
      vector<Myth *> external_myths;
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

      void add_external_myth(Myth &myth) {
        external_myths.push_back(&myth);
      }

      void add_renderable(lookinglass::Renderable &renderable);
//      void remove_renderable(lookinglass::Renderable &renderable);
      void update();
      void loop();

//      static void register_myth(Myth_Info *info);
      Client &get_client() const {
        return *client;
      }

      void add_myth(Myth *myth);
  };
}