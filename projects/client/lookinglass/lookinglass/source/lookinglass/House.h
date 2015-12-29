#pragma once
#include "dllexport.h"

#include "lookinglass/Frame.h"
#include "Platform_Factory.h"
#include <vector>
#include <memory>

using namespace std;

namespace lookinglass {
  namespace glow {
    class MYTHIC_EXPORT Capabilities;
  }

  namespace shading {
    class MYTHIC_EXPORT Shader_Manager;

    class MYTHIC_EXPORT Shader_Loader;
  }

  using namespace shading;

  class MYTHIC_EXPORT Glass;

  class MYTHIC_EXPORT Renderable;

  class MYTHIC_EXPORT House {
  private:
      unique_ptr<glow::Capabilities> capabilities;
      vector<Renderable *> renderables;
      unique_ptr<Shader_Manager> shader_manager;
      unique_ptr<Glass> glass;
      unique_ptr<Frame> frame;

  public:

      House(Frame *frame, Shader_Loader *shader_loader);
      House(Platform_Factory &factory);
      ~House();
      void update();
      bool is_closing();
      void add_renderable(Renderable *renderable);
      void remove_renderable(Renderable *renderable);

      Glass &getGlass() const {
        return *glass;
      }

      Frame &getFrame() const {
        return *frame;
      }

      const Shader_Manager &getShader_manager() const {
        return *shader_manager;
      }
  };
}