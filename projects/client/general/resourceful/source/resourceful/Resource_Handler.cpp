#include "Resource_Handler.h"

namespace resourceful {

  Resource_Handler::~Resource_Handler() {
  }

//  void Light_Resource_Manager::remove_resource(Resource *resource) {
//    for (int i = 0; i < resources.size(); ++i) {
//      if (resources[i].lock().get() == resource) {
//        resources.erase(resources.begin() + i);
//        return;
//      }
//    }
//  }
  void Resource_Handler::add_resource(const std::shared_ptr<Resource> &resource) {
    for (auto &current: resources) {
      if (current.expired()) {
        current = resource;
        return;
      }
    }

    resources.push_back(std::weak_ptr<Resource>(resource));
  }

//  void Resource_Handler::prune() {
//    for (int i = resources.size() - 1; i >= 0; --i) {
//      if (resources[i].expired()) {
//        resources.erase(resources.begin() + i);
//      }
//    }
//  }

  void Resource_Handler::release() {
    for (auto &resource: resources) {
      if (!resource.expired())
        resource.lock()->release();
    }
  }

  void Resource_Handler::load() {
    for (auto &resource: resources) {
      if (!resource.expired())
        resource.lock()->load();
    }
  }
}
