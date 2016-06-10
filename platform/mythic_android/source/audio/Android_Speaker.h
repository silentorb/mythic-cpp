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
    vector<Sample_Type> buffers[3];
    int buffer_index = 0;
    vector<float> float_buffer;
    audio::Device_Settings device_settings;

public:
    virtual audio::Device_Settings start() override;
    virtual void stop() override;

    virtual ~Android_Speaker();

    void update_buffers();
    void free();
};
