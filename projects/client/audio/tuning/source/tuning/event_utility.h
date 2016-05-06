#pragma once

#include "dllexport.h"
#include "Event_Data.h"

namespace tuning {

  MYTHIC_EXPORT void write_events_to_file(Event_Data &source, const string &filename);
}