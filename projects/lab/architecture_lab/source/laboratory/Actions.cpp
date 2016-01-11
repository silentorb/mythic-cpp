#include "Actions.h"

namespace laboratory {
#undef ACTION
#define ACTION(name) Action *Actions::name;
#include "action-definitions.h"
}
