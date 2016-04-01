#include <aura/Speaker.h>
#include "interface.h"
#include "Desktop_Speaker.h"

aura::Speaker* desktop_create_speaker() {
    return new desktop::Desktop_Speaker();
}