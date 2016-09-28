#include "glow.h"
#include "glow_gl.h"

namespace glow {

  bool initialize_desktop() {
#if _MSC_VER
    if (!gladLoadGL()) {
      return false;
    }
#elif __APPLE__
#elif __ANDROID__
#else
    if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
      return false;
    }
#endif
    return true;
  }

  namespace cache {
    bool blend = false;
    bool culling = false;
    bool depth_test = false;
    bool depth_write = false;
    bool scissor_box = false;
    float line_width = 1;
    glm::vec4 clear_color;
    Blend_Factor source = Blend_Factor::one;
    Blend_Factor destination = Blend_Factor::zero;

    unsigned int default_framebuffer = 0;
    unsigned int array_buffer = 0;
    unsigned int element_array_buffer = 0;
  }

  void toggle(GLenum setting, bool value) {
//		throw runtime_error("temp");
    if (value)
      glEnable(setting);
    else
      glDisable(setting);

  }

  void set_depth_test(bool value) {
    if (cache::depth_test == value)
      return;

    cache::depth_test = value;
    toggle(GL_DEPTH_TEST, value);
  }

  void set_depth_write(bool value) {
    if (cache::depth_write == value)
      return;

    cache::depth_write = value;
    glDepthMask(value);
  }

  void set_culling(bool value) {
    if (cache::culling == value)
      return;

    cache::culling = value;
    toggle(GL_CULL_FACE, value);
  }

  void set_blend(bool value) {
    if (cache::blend == value)
      return;

    cache::blend = value;
    toggle(GL_BLEND, value);
  }

  void enable_scissor_box(float left, float top, float width, float height) {
    if (!cache::scissor_box)
      glEnable(GL_SCISSOR_TEST);

    cache::scissor_box = true;
    glScissor(left, top, width, height);
  }

  void disable_scissor_box() {
    if (!cache::scissor_box)
      return;

    cache::scissor_box = false;
    glDisable(GL_SCISSOR_TEST);
  }

  void set_line_thickness(float value) {
    if (cache::line_width == value)
      return;

    cache::line_width = value;
    glLineWidth(value);
  }

  void set_clear_color(const glm::vec4 &value) {
    if (cache::clear_color == value)
      return;

    cache::clear_color = value;
    glClearColor(value.r, value.g, value.b, value.a);
  }

  const glm::vec4 &get_clear_color() {
    return cache::clear_color;
  }

  void set_blend_function(Blend_Factor source, Blend_Factor destination) {
    if (cache::source == source && cache::destination == destination)
      return;

    cache::source = source;
    cache::destination = destination;
    glBlendFunc(static_cast<GLenum>(cache::source), static_cast<GLenum>(cache::destination));
  }

  void set_default_framebuffer(unsigned int id) {
    cache::default_framebuffer = id;
  }

  unsigned int get_default_framebuffer() {
    return cache::default_framebuffer;
  }

  void set_array_buffer(unsigned int id) {
    if (cache::array_buffer == id)
      return;

    cache::array_buffer = id;
//    cache::element_array_buffer = 0;
    glBindBuffer(GL_ARRAY_BUFFER, id);
  }
    
    unsigned int get_array_buffer() {
        return cache::array_buffer;
    }

  void set_element_array_buffer(unsigned int id) {
    if (cache::element_array_buffer == id)
      return;

    cache::element_array_buffer = id;
//    cache::array_buffer = 0;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  }
}

