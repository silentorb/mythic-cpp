#include "Generator.h"

using namespace std;

namespace aura {

  Instrumental_Generator Literal(float value) {
    return Instrumental_Generator([value](const sequencing::Note&) {
      return [value]() {
        return value;
      };
    });
  }


}
