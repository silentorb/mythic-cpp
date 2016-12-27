#pragma once

#include <string>

namespace debugging {

  const std::string get_stack_trace(int max_frames = 10);
}