#pragma once


#include "Graphic_Options.h"
#include <vector>
#include <memory>
#include <functional>
#include <glm/vec2.hpp>
#include <perspective/Camera.h>

namespace shading {
  class Shader_Loader;

  class Shader_Manager;
}

namespace perspective {
  struct Viewport_Data;

  class Viewport;

}
using namespace perspective;

using namespace std;

namespace glow {
  class Capabilities;

  class Version;
}
namespace framing {
  class Platform_Frame;

  class Frame_Info;
}

namespace resourceful {
  class Resource;

  class Resource_Handler;
}

namespace through {
  template<typename T>
  class Mist;
}

namespace texturing {
  namespace buffering {
    class Frame_Buffer;

    class Render_Buffer;
  }
}
namespace lookinglass {

  using namespace through;

  class Glass;

  typedef function<void()> Renderable;

  class Lookinglass_Resources;

  class House {
  protected:
      unique_ptr<Mist<Viewport_Data>> viewport_mist;
      unique_ptr<Viewport> base_viewport;
      Viewport *active_viewport = nullptr;
      unique_ptr<Glass> glass;
      unique_ptr<framing::Platform_Frame> frame;
      bool active;
//      vector<Renderable> renderables;
      Renderable renderable;
      unique_ptr<Lookinglass_Resources> resource_manager;
      unique_ptr<resourceful::Resource_Handler> resource_handler;
      static House *instance;

      void initialize();
      House(framing::Platform_Frame *frame, const Graphic_Options &options);
      Graphic_Options options;
      unique_ptr<glow::Capabilities> capabilities;

      std::shared_ptr<texturing::buffering::Frame_Buffer> frame_buffer;
      std::shared_ptr<texturing::buffering::Render_Buffer> color_buffer;
      std::shared_ptr<texturing::buffering::Render_Buffer> depth_buffer;

  public:

      ~House();
      void render();
      bool is_closing();
//      void remove_renderable(Renderable &renderable);

      Glass &get_glass() const {
        return *glass;
      }

      framing::Frame_Info &get_frame() const;

      Viewport &get_base_viewport() const {
        return *base_viewport;
      }

      bool is_active() const {
        return active;
      }

      void set_active(bool value) {
        active = value;
      }

      void release();
      void load();

      Lookinglass_Resources &get_resources() const;

      shading::Shader_Manager &get_shader_manager() const;

      const glm::ivec2 &get_dimensions();

      Mist<Viewport_Data> &get_viewport_mist() const {
        return *viewport_mist;
      }

      static House &get_instance();

      resourceful::Resource_Handler &get_resource_handler() const {
        return *resource_handler;
      }

      void watch_resource(const std::shared_ptr<resourceful::Resource> &resource);

      const Graphic_Options &get_options() const {
        return options;
      }

      const glow::Version &get_version() const;
      glow::Capabilities &get_capabilities() const;

      texturing::buffering::Frame_Buffer &get_frame_buffer() const;
      void set_renderable(const Renderable &renderable);
  };
}