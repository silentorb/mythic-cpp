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

    SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
    want.freq = 44100;
    want.format = AUDIO_F32;
    want.channels = 2;
    want.samples = 4096;
//    want.samples = 4096;
    want.callback = audio_callback;  // you wrote this function elsewhere.
    want.userdata = this;

    device = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
    if (device == 0) {
      throw runtime_error(string("Failed to open audio: %s\n") + SDL_GetError());
    } else {
      if (have.format != want.format) { // we let this one thing change.
        throw runtime_error("We didn't get Float32 audio format.\n");
      }
      SDL_PauseAudioDevice(device, 0); // start audio playing.
//      SDL_Delay(5000);  // let the audio callback play some sound for 5 seconds.
    }

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