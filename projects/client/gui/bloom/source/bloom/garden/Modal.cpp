#include <bloom/old/Button_Old.h>
#include "Modal.h"

namespace bloom {

  void get_buttons(Flower_Old *flower, vector<Flower_Old *> &buttons) {
    for (auto &child : flower->get_children()) {
//      if (dynamic_cast<Button_Old *>(child.get())) {
//        buttons.push_back(child.get());
//      }

      get_buttons(child.get(), buttons);
    }
  }

  Modal::Modal(Flower_Old *root) :
    old_root(root) {

    get_buttons(root, buttons);
  }

  Modal::Modal(flowers:: Flower *root) :
    root(root) {

//    get_buttons(root, buttons);
  }
}