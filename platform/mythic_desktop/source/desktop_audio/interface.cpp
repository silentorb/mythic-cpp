#include <audio/Speaker.h>
#include "interface.h"
#include "Desktop_Speaker.h"

audio::Speaker* desktop_create_speaker() {
    return new desktop::Desktop_Speaker();
}