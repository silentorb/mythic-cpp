#pragma once

#include "dllexport.h"
#include "audio/Speaker.h"
#include <mutex>
#include <vector>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

using namespace std;

typedef short Sample_Type;
class MYTHIC_EXPORT Android_Speaker : public audio::Speaker {
    void initialize_sl_engine();
    void initialize_buffer();
    mutex buffer_mutex;

    vector<Sample_Type> buffers[2];
    vector<Sample_Type> *active_buffer;
    vector<Sample_Type> *next_buffer;

    vector<float> float_buffer;
//    vector<float> *active_buffer2;
//    vector<float> *next_buffer2;

    audio::Device_Settings device_settings;

public:
    virtual audio::Device_Settings start() override;
    virtual void stop() override;

    void update_buffers(SLAndroidSimpleBufferQueueItf bq);
};
