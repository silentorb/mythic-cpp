
create_library(logger)
require(commoner)

if (ANDROID)
  add_sources(platform/logger-android.cpp)
else ()
  add_sources(platform/logger-desktop.cpp)
endif ()