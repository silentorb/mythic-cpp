#include "Mythic_Renderer.h"
#include "vectoring/utility.h"

namespace mythic {

  void Mythic_Renderer::render() {
    for(auto &renderable: renderables){
      renderable();
    }
  }

  void Mythic_Renderer::add_renderable(Renderable renderable) {
    renderables.push_back(renderable);
  }

//  void Mythic_Renderer::remove_renderable(Renderable *renderable) {
//    vector_remove(renderables,renderable);
//  }
}