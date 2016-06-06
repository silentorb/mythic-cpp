#pragma once

#include "dllexport.h"
#include "audio/Speaker.h"

class MYTHIC_EXPORT Android_Speaker : public audio::Speaker {

public:
    virtual audio::Device_Settings start() override;
    virtual void stop() override;

};
