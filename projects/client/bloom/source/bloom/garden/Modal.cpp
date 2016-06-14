#include <bloom/flowers/Button.h>
#include "Modal.h"

namespace bloom {

  void get_buttons(Flower *flower, vector<Flower *> &buttons) {
    for (auto &child : flower->get_children()) {
      if (dynamic_cast<Button *>(child.get())) {
        buttons.push_back(child.get());
      }

      get_buttons(child.get(), buttons);
    }
  }

  Modal::Modal(Flower *root) :
    root(root) {

    get_buttons(root, buttons);
  }
}