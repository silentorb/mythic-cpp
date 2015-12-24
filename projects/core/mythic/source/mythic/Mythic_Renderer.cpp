#include "Mythic_Renderer.h"
#include "vectoring/utility.h"

namespace mythic {

  void Mythic_Renderer::render(Glass &glass) {
    for(auto renderable: renderables){
      renderable->render(glass);
    }
  }

  void Mythic_Renderer::add_renderable(Renderable *renderable) {
    renderables.push_back(renderable);
  }

  void Mythic_Renderer::remove_renderable(Renderable *renderable) {
    vector_remove(renderables,renderable);
  }
}