#include "Renderable_List.h"
#include <algorithm>

//namespace lookinglass {
//
//  Renderable_List::~Renderable_List() {
//    for (auto renderable: renderables) {
//      delete renderable;
//    }
//  }
//
//  void Renderable_List::add(Renderable &renderable) {
//    renderables.push_back(&renderable);
////    renderable.set_renderable_list(*this);
//  }
//
//  void Renderable_List::remove(Renderable &renderable) {
//    renderables.erase(std::remove(renderables.begin(), renderables.end(), &renderable), renderables.end());
//  }
//
//  void Renderable_List::render(Glass &glass) {
//    for (auto renderable : renderables) {
//      renderable->render(glass);
//    }
//  }
//
//}