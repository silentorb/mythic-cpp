//#include <scenery/elements/Model.h>
//#include "Scene.h"
//#include <algorithm>
//
//namespace scenery {
//
//  void Scene::render(Glass &glass) {
//    for (auto &element: elements) {
//      if (element->is_visible())
//        element->render(glass);
//    }
//  }
//
//  void Scene::add_child(unique_ptr<Element> element) {
//    elements.push_back(std::move(element));
//
//  }
//
//  bool Scene::has_transform() {
//    return false;
//  }
//
//  mat4 Scene::get_transform() {
//    throw runtime_error("Not supported.");
//  }
//
//  void Scene::move_child(unique_ptr<Element> &element, Parent &destination) {
////    destination.add(std::move(element));
////    auto offset = std::find(elements.begin(), elements.end(), [=](std::unique_ptr<int> &p) {
////      return p.get() == nullptr;
////    }) - elements.begin();
////    elements.erase(elements.begin() + offset);
////    elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
//  }
//
//  void Scene::move_child(Element &element, Parent &destination) {
//    int offset = std::find_if(elements.begin(), elements.end(), [&](unique_ptr<Element> const &item) {
//      return item.get() == &element;
//    }) - elements.begin();
//
//    destination.add_child(std::move(elements[offset]));
//    elements.erase(elements.begin() + offset);
//  }
//
//  void Scene::remove_child(Element &element) {
//    int offset = std::find_if(elements.begin(), elements.end(), [&](unique_ptr<Element> const &item) {
//      return item.get() == &element;
//    }) - elements.begin();
//
//    elements.erase(elements.begin() + offset);
//  }
//}
