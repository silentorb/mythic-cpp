#pragma once

#include "commoner/dllexport.h"

#include "Myth.h"
#include <map>
#include <memory>
#include "Myth_Info.h"
#include <functional>
#include <vector>

namespace timing {
  class Quartz;
}

namespace clienting {
  class Client;
}

namespace lookinglass {
  typedef function<void()> Renderable;

  class Graphic_Options;
}
using namespace clienting;
using namespace std;

namespace mythic {

  class Mythic_Renderer;

  class Platform_Factory;

  class MYTHIC_EXPORT Mythic_Engine : no_copy {
      unique_ptr<timing::Quartz> timer;
      unique_ptr<Client> client;
      std::map<string, unique_ptr<Myth>> myths;
      vector<Myth *> external_myths;
      unique_ptr<Mythic_Renderer> renderer;
      const string storage_path;

  public:
      Mythic_Engine(Platform_Factory &factory, const lookinglass::Graphic_Options &graphic_options);
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

      void update();
      void loop();

//      static void register_myth(Myth_Info *info);
      Client &get_client() const {
        return *client;
      }

      void add_myth(Myth *myth);

      const string &get_storage_path() const {
        return storage_path;
      }
  };
}