#include "Lookinglass_House.h"
#include "glow.h"
#include "glow_gl.h"
#include "glow/Capabilities.h"
#include "perspective/Viewport.h"
#include "through/create_mist.h"
#include "Lookinglass_Resources.h"
#include "shading/Shader_Manager.h"
#include "lookinglass/Renderable_List.h"
#include "typography/Text_Effect.h"
#include "framing/Platform_Frame.h"
#include <texturing/buffering/Render_Buffer.h>
#include <texturing/buffering/Frame_Buffer.h>

using namespace through;

namespace lookinglass {

  Lookinglass_House::Lookinglass_House(framing::Platform_Frame *frame, resourceful::File_Loader file_loader,
                                       shading::Shader_Processor shader_processor, const Graphic_Options &options) :
    House(frame, options) {
    if (!frame) {
      throw std::runtime_error("Frame (Window) was null.");
    }
//#define GL2_0
#ifdef GL2_0
    auto version = glow::Version(2, 0);
#else
    auto version = glow::Version();
#endif
    capabilities = unique_ptr<glow::Capabilities>(new Capabilities(version));

    auto &dimensions = frame->get_dimensions();

    auto scene_definition = new Struct_Info(1, "", {
      {"view", Field_Type::matrix},
      {"projection", Field_Type::matrix},
      {"camera_direction", Field_Type::vector3}
    });
    viewport_mist = unique_ptr<Mist<Viewport_Data>>(
      through::create_mist<Viewport_Data>(scene_definition));
    base_viewport = unique_ptr<Viewport>(new Viewport(*viewport_mist, dimensions.x, dimensions.y));
    base_viewport->activate();

    resource_manager = unique_ptr<Lookinglass_Resources>(
      new Lookinglass_Resources(file_loader, shader_processor, *base_viewport));

    resource_manager->get_shader_manager().add_program_add_listener(*viewport_mist);

//    base_viewport->add_listener(Vector2_Delegate(
//      [&](const ivec2 &dimensions) { resource_manager->get_text_effect().set_viewport_dimensions(dimensions); }));

    glass = unique_ptr<Glass>(new Glass(get_base_viewport()));
    initialize();

//    frame_buffer = shared_ptr<texturing::buffering::Frame_Buffer>(new texturing::buffering::Frame_Buffer());
//    watch_resource(frame_buffer);
//
//    color_buffer = shared_ptr<texturing::buffering::Render_Buffer>(
//      new texturing::buffering::Render_Buffer(dimensions, GL_RGBA8, options.get_multisamples()));
//    watch_resource(color_buffer);
//
//    depth_buffer = shared_ptr<texturing::buffering::Render_Buffer>(
//      new texturing::buffering::Render_Buffer(dimensions, GL_DEPTH_COMPONENT, options.get_multisamples()));
//    watch_resource(depth_buffer);
//
//    frame_buffer->attach_render_buffer(color_buffer, GL_COLOR_ATTACHMENT0);
//    frame_buffer->attach_render_buffer(depth_buffer, GL_DEPTH_ATTACHMENT);
//        frame_buffer->check_complete();
//    texturing::buffering::Frame_Buffer::deactivate();
  }

}