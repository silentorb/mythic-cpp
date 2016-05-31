#include "Resource_Manager.h"

namespace resourceful {

  Resource_Manager::~Resource_Manager() {
int k = 0;
  }

  void Resource_Manager::remove_resource(Resource *resource) {
    for (int i = 0; i < resources.size(); ++i) {
      if (resources[i].get() == resource) {
        resources.erase(resources.begin() + i);
        return;
      }
    }
  }

//
//  void Resource_Manager::free() {
//    for (auto &resource: resources) {
//      resource->free();
//    }
//  }
//
//  void Resource_Manager::load() {
//    for (auto &resource: resources) {
//      resource->load();
//    }
//  }
}
