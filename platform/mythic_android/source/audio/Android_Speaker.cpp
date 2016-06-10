#include "Android_Speaker.h"
#include "audio/Device_Settings.h"
#include <stdexcept>

#include <assert.h>

using namespace std;
static SLObjectItf engineObject = NULL;
static SLEngineItf engineEngine;

// output mix interfaces
static SLObjectItf outputMixObject = NULL;
static SLEnvironmentalReverbItf outputMixEnvironmentalReverb = NULL;

// pointer and size of the next player buffer to enqueue, and number of remaining buffers

static SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue;

static SLObjectItf bqPlayerObject = NULL;
static SLPlayItf bqPlayerPlay;

audio::Device_Settings Android_Speaker::start() {
  device_settings = {
    44100,
    4096,
    2
  };

  initialize_sl_engine();
  initialize_buffer();

  return device_settings;
}

void Android_Speaker::initialize_sl_engine() {
  SLresult result;

  // create engine
  result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // realize the engine
  result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // get the engine interface, which is needed in order to create other objects
  result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // create output mix, with environmental reverb specified as a non-required interface
  const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
  const SLboolean req[1] = {SL_BOOLEAN_FALSE};
  result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 0, ids, req);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // realize the output mix
  result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

}

void Android_Speaker::update_buffers(SLAndroidSimpleBufferQueueItf bq) {
  SLresult result;
//  unique_lock<mutex>(buffer_mutex);

  result = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, next_buffer->data(), next_buffer->size());
  auto temp_buffer = active_buffer;
  active_buffer = next_buffer;
  next_buffer = temp_buffer;

  update(float_buffer.data(), float_buffer.size() * sizeof(Sample_Type));

  for (int i = 0; i < float_buffer.size(); ++i) {
    (*next_buffer)[i] = (short)(float_buffer[i] * 32767);
  }
}

void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context) {
  assert(bq == bqPlayerBufferQueue);
  assert(context != nullptr);

  auto speaker = (Android_Speaker *) context;
  speaker->update_buffers(bq);
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
  pcm.channelMask = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
  pcm.endianness = SL_BYTEORDER_LITTLEENDIAN;

  SLDataSource audioSrc = {&loc_bufq, &pcm};

  // configure audio sink
  SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
  SLDataSink audioSnk = {&loc_outmix, NULL};

  const SLInterfaceID ids[1] = {SL_IID_BUFFERQUEUE};
  const SLboolean req[1] = {SL_BOOLEAN_TRUE};

  result = (*engineEngine)->CreateAudioPlayer(engineEngine, &bqPlayerObject, &audioSrc, &audioSnk,
                                              1, ids, req);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  result = (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // get the play interface
  result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &bqPlayerPlay);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // get the buffer queue interface
  result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE,
                                           &bqPlayerBufferQueue);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  // register callback on the buffer queue
  result = (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue, bqPlayerCallback, this);
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

//  // get the volume interface
//  result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_VOLUME, &bqPlayerVolume);
//  assert(result == SL_RESULT_SUCCESS);
//  (void) result;

  // set the player's state to playing
  result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
  assert(result == SL_RESULT_SUCCESS);
  (void) result;

  buffers[0].resize(device_settings.buffer_size);
  buffers[1].resize(device_settings.buffer_size);
  float_buffer.resize(device_settings.buffer_size);
  active_buffer = &buffers[0];
  next_buffer = &buffers[1];

  update_buffers(bqPlayerBufferQueue);
}

void Android_Speaker::stop() {

}

