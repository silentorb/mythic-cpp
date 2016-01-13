#pragma once

#include "dllexport.h"
#include <vector>
#include "Resource.h"
#include <memory>
#include <string>

using namespace std;

namespace resourceful {

  class MYTHIC_EXPORT Resource_Manager : public Resource {
      const string name;
      vector<unique_ptr<Resource>> resources;
      Resource_Manager &operator=(const Resource_Manager &) = delete;
      Resource_Manager(Resource_Manager const &) = delete;
  public:
      Resource_Manager(const string name) : name(name) { }

//      void free() override;
//      void load() override;

      void free() override {
        for (auto &resource: resources) {
          resource->free();
        }
      }

      void load() override {
        for (auto &resource: resources) {
          resource->load();
        }
      }

      void add_resource(Resource *resource) {
        resources.push_back(unique_ptr<Resource>(resource));
      }

  };

}
