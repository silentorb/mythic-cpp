#pragma once

#include "commoner/dllexport.h"
#include "Event_Data.h"

namespace tuning {

  void write_events_to_file(Event_Data &source, const string &filename);
  void write_notation_to_file(Event_Data &source, const string &filename);
}