#include "House.h"
#include "lookinglass/glow.h"

namespace lookinglass {
  House::House(Frame *frame) :
    frame(frame),
    glass(new Glass()) {

    frame->set_clear_color(0, 0.1f, 0.3f, 1);
  }

  House::~House() {
    delete glass;
  }

  void House::start_update() {
    frame->clear();
    frame->update();
  }

  void House::finish_update() {
    frame->flip_buffer();
  }

  bool House::is_closing() {
    return frame->closing;
  }


}