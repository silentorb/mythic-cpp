#pragma once
#include "dllexport.h"
#include <memory>
#include "resourceful/Resource.h"
#include <string>

using namespace std;

namespace audio {

    class MYTHIC_EXPORT Waveform: resourceful::Resource {
        virtual void load() override;
        virtual void free() override;
        unique_ptr<char> buffer;
        const string filename;

        Waveform(const string &filename);

    };
}