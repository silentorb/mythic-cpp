#include "Android_Speaker.h"
#include "audio/Device_Settings.h"
#include <stdexcept>
#include "logger.h"
#include <assert.h>

using namespace std;
static SLObjectItf engine_object = NULL;
static SLEngineItf engine_interface;

// output mix interfaces
static SLObjectItf output_mix_object = NULL;
static SLVolumeItf bqPlayerVolume = nullptr;

static SLAndroidSimpleBufferQueueItf buffer_queue;

static SLObjectItf player_object = NULL;
static SLPlayItf buffer_play;

#define SAWTOOTH_FRAMES 8000
static short sawtoothBuffer[SAWTOOTH_FRAMES];
static vector<short> sawtooth;
audio::Device_Settings Android_Speaker::start() {
  device_settings = {
    44100,
    4096,
    1
  };
  sawtooth.resize(SAWTOOTH_FRAMES);
  unsigned i;
  for (i = 0; i < SAWTOOTH_FRAMES; ++i) {
    sawtoothBuffer[i] = 32768 - ((i % 100) * 660);
    sawtooth[i] = 32768 - ((i % 100) * 660);
  }


  initialize_sl_engine();
  initialize_buffer();

  return device_settings;
}

void Android_Speaker::initialize_sl_engine() {
  SLresult result;

  // create engine
  result = slCreateEngine(&engine_object, 0, NULL, 0, NULL, NULL);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // realize the engine
  result = (*engine_object)->Realize(engine_object, SL_BOOLEAN_FALSE);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // get the engine interface, which is needed in order to create other objects
  result = (*engine_object)->GetInterface(engine_object, SL_IID_ENGINE, &engine_interface);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // create output mix
  result = (*engine_interface)->CreateOutputMix(engine_interface, &output_mix_object, 0, nullptr, nullptr);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // realize the output mix
  result = (*output_mix_object)->Realize(output_mix_object, SL_BOOLEAN_FALSE);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

}
unsigned long istep;
void Android_Speaker::update_buffers() {
  SLresult result;
//  unique_lock<mutex>(buffer_mutex);
//  log_info("Updating audio buffer %d.", buffer_index);
  auto next_buffer = &buffers[buffer_index];
  update(float_buffer.data(), float_buffer.size() * sizeof(float));

  for (int i = 0; i < next_buffer->size(); ++i) {
//    next_buffer->data()[i] = (short) (float_buffer[i] * 32767);
    next_buffer->data()[i] = (short) (float_buffer[i] * 32767 / 3);
//    (*next_buffer)[i] = (rand() % (2 * 32767)) - 32767;
//    (*next_buffer)[i] = 32768 - ((istep++ % 100) * 660);
  }
  result = (*buffer_queue)->Enqueue(buffer_queue, next_buffer->data(), next_buffer->size() * sizeof(Sample_Type));
//  result = (*buffer_queue)->Enqueue(buffer_queue, sawtooth.data(), sawtooth.size() * sizeof(Sample_Type));

  assert(result == SL_RESULT_SUCCESS);
  (void) result;
//  auto temp_buffer = active_buffer;
//  active_buffer = next_buffer;
//  next_buffer = temp_buffer;

  buffer_index = (buffer_index + 1) % 3;
}

void buffer_queue_callback(SLAndroidSimpleBufferQueueItf bq, void *context) {
  assert(bq == buffer_queue);
  assert(context != nullptr);

  auto speaker = (Android_Speaker *) context;
  speaker->update_buffers();
}

void Android_Speaker::initialize_buffer() {

  SLresult result;

  SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
//  SLDataFormat_PCM format_pcm = {SL_ANDROID_DATAFORMAT_PCM_EX, device_settings.channel_count, SL_SAMPLINGRATE_8,
//                                 SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
//                                 SL_SPEAKER_FRONT_CENTER, SL_BYTEORDER_LITTLEENDIAN};

  SLDataFormat_PCM pcm;
  pcm.formatType = SL_DATAFORMAT_PCM;
  pcm.numChannels = device_settings.channel_count;
  pcm.samplesPerSec = SL_SAMPLINGRATE_44_1;
  pcm.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
  pcm.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
  pcm.channelMask = device_settings.channel_count == 1
                    ? SL_SPEAKER_FRONT_CENTER
                    : SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
  pcm.endianness = SL_BYTEORDER_LITTLEENDIAN;

  SLDataSource audioSrc = {&loc_bufq, &pcm};

  // configure audio sink
  SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, output_mix_object};
  SLDataSink audioSnk = {&loc_outmix, NULL};

  const SLInterfaceID ids[2] = {SL_IID_ANDROIDSIMPLEBUFFERQUEUE, SL_IID_VOLUME};
  const SLboolean req[2] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};

  result = (*engine_interface)->CreateAudioPlayer(engine_interface, &player_object, &audioSrc, &audioSnk,
                                                  2, ids, req);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  result = (*player_object)->Realize(player_object, SL_BOOLEAN_FALSE);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // get the play interface
  result = (*player_object)->GetInterface(player_object, SL_IID_PLAY, &buffer_play);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // get the buffer queue interface
  result = (*player_object)->GetInterface(player_object, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &buffer_queue);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // register callback on the buffer queue
  result = (*buffer_queue)->RegisterCallback(buffer_queue, buffer_queue_callback, this);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // get the effect send interface
//  bqPlayerEffectSend = NULL;
//  if (0 == bqPlayerSampleRate) {
//    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_EFFECTSEND,
//                                             &bqPlayerEffectSend);
//    assert(result == SL_RESULT_SUCCESS);
//    (void) result;
//  }

  // get the volume interface
  result = (*player_object)->GetInterface(player_object, SL_IID_VOLUME, &bqPlayerVolume);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // set the player's state to playing
  result = (*buffer_play)->SetPlayState(buffer_play, SL_PLAYSTATE_PLAYING);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

//  SLmillibel volume_level;
//  SLmillibel max_volume_level;
//
//  result = (*bqPlayerVolume)->GetVolumeLevel(bqPlayerVolume, &volume_level);
//  assert(result == SL_RESULT_SUCCESS);
//  (void) result;
//
//
//  result = (*bqPlayerVolume)->GetMaxVolumeLevel(bqPlayerVolume, &max_volume_level);
//  assert(result == SL_RESULT_SUCCESS);
//  (void) result;
//  log_info("Volume: %d", volume_level);
//
//  log_info("Volume: %d / %d", volume_level, max_volume_level);
//
//  result = (*bqPlayerVolume)->SetVolumeLevel(bqPlayerVolume, max_volume_level);
//  assert(SL_RESULT_SUCCESS == result);
//  (void)result;
//
//  result = (*bqPlayerVolume)->GetVolumeLevel(bqPlayerVolume, &volume_level);
//  assert(result == SL_RESULT_SUCCESS);
//  (void) result;
//  log_info("Volume: %d", volume_level);

  auto buffer_size = device_settings.buffer_size / sizeof(Sample_Type) / device_settings.channel_count;
  buffers[0].resize(buffer_size);
  buffers[1].resize(buffer_size);
  buffers[2].resize(buffer_size);
  float_buffer.resize(buffer_size);
//  active_buffer = &buffers[0];
//  next_buffer = &buffers[1];

  update_buffers();
  update_buffers();
  log_info("Audio started.");
}

void Android_Speaker::stop() {

}

Android_Speaker::~Android_Speaker() {
  free();
}

void Android_Speaker::free() {
  // destroy buffer queue audio player object, and invalidate all associated interfaces
  if (player_object != NULL) {
    (*player_object)->Destroy(player_object);
    player_object = NULL;
    buffer_play = NULL;
    buffer_queue = NULL;
  }

  // destroy output mix object, and invalidate all associated interfaces
  if (output_mix_object != NULL) {
    (*output_mix_object)->Destroy(output_mix_object);
    output_mix_object = NULL;
  }

  // destroy engine object, and invalidate all associated interfaces
  if (engine_object != NULL) {
    (*engine_object)->Destroy(engine_object);
    engine_object = NULL;
    engine_interface = NULL;
  }
}

