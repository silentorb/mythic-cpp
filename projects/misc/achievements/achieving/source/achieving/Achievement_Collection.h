#pragma once

#include <map>
#include <string>
#include "Achievement.h"
#include <memory>

namespace achieving {

//  using Achievement_Definition_Collection = std::map<std::string, Achievement_Definition>;
  using Achievement_Collection = std::map<std::string, std::unique_ptr<Achievement>>;

}