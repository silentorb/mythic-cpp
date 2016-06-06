#include "Android_Speaker.h"
#include <stdexcept>

using namespace std;

audio::Device_Settings Android_Speaker::start() {

  return {
    44100,
    4096,
    2
  };
}

void Android_Speaker::stop() {

}

