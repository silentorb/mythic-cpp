#pragma once

#include "dllexport.h"
#include "framing/Frame.h"
#include <vector>
#include <memory>
#include <functional>

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
}

namespace lookinglass {

  namespace through {
    template<typename T>
    class Mist;
  }
  using namespace through;

  class Glass;

  typedef function<void()> Renderable;

  class Lookinglass_Resources;

  class MYTHIC_EXPORT House {
  protected:
      unique_ptr<Mist<Viewport_Data>> viewport_mist;
      unique_ptr<Viewport> base_viewport;
      unique_ptr<Glass> glass;
      unique_ptr<framing::Frame> frame;
      bool active;
      vector<Renderable> renderables;
      unique_ptr<Lookinglass_Resources> resource_manager;
      static House *instance;

      void initialize();
      House(framing::Frame *frame);

  public:

      ~House();
      void update();
      bool is_closing();
      void add_renderable(Renderable renderable);
//      void remove_renderable(Renderable &renderable);

      Glass &get_glass() const {
        return *glass;
      }

      framing::Frame &get_frame() const {
        return *frame;
      }

      Viewport &get_base_viewport() const {
        return *base_viewport;
      }

      bool is_active() const {
        return active;
      }

      void set_active(bool value) {
        active = value;
      }

      void free();
      void load();

      Lookinglass_Resources &get_resources() const;

      shading::Shader_Manager &get_shader_manager() const;

      const glm::ivec2 &get_dimensions();

      Mist<Viewport_Data> &get_viewport_mist() const {
        return *viewport_mist;
      }

      static House &get_instance();
  };
}