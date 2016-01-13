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

    class Shader_Loader;
  }
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

  class Glass;

  class Renderable;

  class Lookinglass_Resources;

  class MYTHIC_EXPORT House {
  private:
      unique_ptr<Mist<Viewport_Data>> viewport_mist;
      unique_ptr<glow::Capabilities> capabilities;
      vector<Renderable *> renderables;
      unique_ptr<Viewport> base_viewport;
      unique_ptr<Glass> glass;
      unique_ptr<Frame> frame;
      bool active;

      unique_ptr<Lookinglass_Resources> resource_manager;
      void initialize();
  public:

      House(Frame *frame, shading::Shader_Loader *shader_loader);
      ~House();
      void update();
      bool is_closing();
      void add_renderable(Renderable *renderable);
      void remove_renderable(Renderable *renderable);

      Glass &get_glass() const {
        return *glass;
      }

      Frame &get_frame() const {
        return *frame;
      }

//      virtual void set_clear_color(float red, float green, float blue, float alpha) = 0;

//      Shader_Manager &get_shader_manager() const {
//        return *shader_manager;
//      }

      Viewport &get_base_viewport() const {
        return *base_viewport;
      }

      const glow::Capabilities &get_capabilities() const {
        return *capabilities;
      }

      bool is_active() const {
        return active;
      }

      void set_active(bool value) {
        active = value;
      }

      void free();
      void load();

      Lookinglass_Resources& get_resources() const;
  };
}