#include "Desktop_Speaker.h"
#include <stdexcept>
#include <SDL2/SDL.h>

using namespace std;

namespace desktop {

  void audio_callback(void *userdata, Uint8 *stream, int len) {
    auto speaker = (Desktop_Speaker*)userdata;
    speaker->update(stream, len);
  }

  audio::Device_Settings Desktop_Speaker::start() {
    SDL_InitSubSystem(SDL_INIT_AUDIO);
    SDL_AudioSpec want;

    SDL_memset(&want, 0, sizeof(want));
    want.freq = 44100;
    want.format = AUDIO_F32;
    want.channels = 2;
    want.samples = 4096;
    want.callback = audio_callback;
    want.userdata = this;

    device = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
    if (device == 0)
      throw runtime_error(string("Failed to open audio: %s\n") + SDL_GetError());

    if (have.format != want.format)
      throw runtime_error("We didn't get Float32 audio format.\n");

    SDL_PauseAudioDevice(device, 0);

    return {
      have.freq,
      have.samples,
      have.channels
    };
  }

  void Desktop_Speaker::stop() {
    SDL_CloseAudioDevice(device);
  }

}
