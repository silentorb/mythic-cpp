#pragma once

#include "dllexport.h"
#include "lookinglass/Frame.h"
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

  namespace perspective {
    struct Viewport_Data;

    class Viewport;

  }
  using namespace perspective;

  namespace through {
    template<typename T>
    class Mist;
  }
  using namespace through;

  class MYTHIC_EXPORT Glass;

  class MYTHIC_EXPORT Renderable;

  class MYTHIC_EXPORT House {
  private:
      unique_ptr<Mist<Viewport_Data>> viewport_mist;
      unique_ptr<glow::Capabilities> capabilities;
      vector<Renderable *> renderables;
      unique_ptr<Shader_Manager> shader_manager;
      unique_ptr<Viewport> base_viewport;
      unique_ptr<Glass> glass;
      unique_ptr<Frame> frame;

  public:

      House(Frame *frame, Shader_Loader *shader_loader);
      ~House();
      void update();
      bool is_closing();
      void add_renderable(Renderable *renderable);
      void remove_renderable(Renderable *renderable);

      Glass &get_glass() const {
        return *glass;
      }

//      Frame &get_frame() const {
//        return *frame;
//      }

      Shader_Manager &get_shader_manager() const {
        return *shader_manager;
      }


      Viewport &get_base_viewport() const {
        return *base_viewport;
      }


      const glow::Capabilities &get_capabilities() const {
        return *capabilities;
      }
  };
}