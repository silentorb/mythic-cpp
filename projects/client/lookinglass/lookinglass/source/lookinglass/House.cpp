#include "House.h"

namespace lookinglass {
  House::House(Frame *frame) :
    frame(frame),
    glass(new Glass()) {
  }

  House::~House() {
    delete glass;
  }

}