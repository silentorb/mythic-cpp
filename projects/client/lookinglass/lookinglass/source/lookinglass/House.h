#pragma once

#include "lookinglass/Frame.h"
#include "Platform_Factory.h"
#include <vector>
#include <memory>

using namespace std;

namespace lookinglass {
  namespace glow {
    class Capabilities;
  }

  namespace shading {
    class Shader_Manager;

    class Shader_Loader;
  }

  using namespace shading;

  class Glass;

  class Renderable;

  class House {
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